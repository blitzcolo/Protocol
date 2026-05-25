#pragma once
#include <array>
#include <bitset>
#include <boost/pfr.hpp>
#include <format>
#include <iterator>
#include <magic_enum/magic_enum.hpp>
#include <optional>
#include <type_traits>
#include <variant>

namespace sculk::protocol::inline abi_v975 {

class IPacket;

namespace formatter {

template <typename T>
    requires std::is_aggregate_v<T>
constexpr std::string toString(const T& value);

namespace detail {

template <typename T>
constexpr bool always_false_v = false;

template <typename T>
struct IsStdVariant : std::false_type {};

template <typename... Ts>
struct IsStdVariant<std::variant<Ts...>> : std::true_type {};

template <typename T>
struct IsStdArray : std::false_type {};

template <typename T, std::size_t N>
struct IsStdArray<std::array<T, N>> : std::true_type {};

template <typename T>
struct IsStdBitset : std::false_type {};

template <std::size_t N>
struct IsStdBitset<std::bitset<N>> : std::true_type {};

namespace concepts {

template <typename T>
concept IsOptional = requires { typename T::value_type; } && requires(T t) {
    t.has_value();
    t.value();
};

template <typename T>
concept IsVector = requires(T t) {
    typename T::value_type;
    t.begin();
    t.end();
};

template <typename T>
concept IsVariant = requires(T t) { typename std::remove_cvref_t<T>; } && IsStdVariant<std::remove_cvref_t<T>>::value;

template <typename T>
concept IsArray = IsStdArray<std::remove_cvref_t<T>>::value;

template <typename T>
concept IsMap = requires(T t) {
    typename T::key_type;
    typename T::mapped_type;
    t.begin();
    t.end();
};

template <typename T>
concept IsBitset = IsStdBitset<std::remove_cvref_t<T>>::value;

} // namespace concepts

template <typename T, typename F>
constexpr void for_each_field_with_name(T&& value, F&& func) {
    return boost::pfr::for_each_field(
        std::forward<T>(value),
        [f = std::forward<F>(func)](auto&& field, auto index) mutable {
            using IndexType     = decltype(index);
            using FieldType     = decltype(field);
            constexpr auto name = boost::pfr::detail::get_name<std::remove_reference_t<T>, IndexType::value>();
            bool           last = (index == boost::pfr::tuple_size_v<std::remove_reference_t<T>> - 1);
            f(name, std::forward<FieldType>(field), last);
        }
    );
}

template <typename T>
constexpr std::string typeToString(const T& value) {
    if constexpr (concepts::IsOptional<T>) {
        return value.has_value() ? typeToString(*value) : "null";
    } else if constexpr (concepts::IsArray<T>) {
        std::string out{"["};
        for (auto it = value.begin(); it != value.end(); ++it) {
            out.append(typeToString(*it));
            if (std::next(it) != value.end()) {
                out.append(", ");
            }
        }
        out.push_back(']');
        return out;
    } else if constexpr (concepts::IsMap<T>) {
        std::string out{"{"};
        for (auto it = value.begin(); it != value.end(); ++it) {
            out.append(std::format("{}: {}", typeToString(it->first), typeToString(it->second)));
            if (std::next(it) != value.end()) {
                out.append(", ");
            }
        }
        out.push_back('}');
        return out;
    } else if constexpr (concepts::IsVector<T>) {
        std::string out{"["};
        for (auto it = value.begin(); it != value.end(); ++it) {
            out.append(typeToString(*it));
            if (std::next(it) != value.end()) {
                out.append(", ");
            }
        }
        out.push_back(']');
        return out;
    } else if constexpr (concepts::IsVariant<T>) {
        return std::visit([](const auto& v) { return typeToString(v); }, value);
    } else if constexpr (concepts::IsBitset<T>) {
        std::string out{"{"};
        for (std::size_t i = 0; i < value.size(); ++i) {
            out.append(std::format("{}: {}", i, value.test(i)));
            if (i + 1 < value.size()) {
                out.append(", ");
            }
        }
        out.push_back('}');
        return out;
    } else if constexpr (std::is_aggregate_v<T>) {
        return toString(value);
    } else if constexpr (std::is_enum_v<T>) {
        auto name            = magic_enum::enum_name(value);
        auto underlyingValue = static_cast<std::underlying_type_t<T>>(value);
        if (name.empty()) {
            return std::format("UnknownEnumValue<{}>", underlyingValue);
        }
        return std::format("{}({})", name, underlyingValue);
    } else if constexpr (std::formattable<T, char>) {
        return std::format("{}", value);
    } else {
        static_assert(always_false_v<T>, "Type cannot be converted to string");
    }
}

} // namespace detail

template <typename T>
void append(std::string& out, std::string_view name, const T& value, bool last) {
    out.append(std::format("{}: {}", name, detail::typeToString(value)));
    if (!last) {
        out.push_back(',');
    }
}

template <typename T>
    requires std::is_aggregate_v<T>
constexpr std::string toString(const T& value) {
    std::string out{"{"};
    detail::for_each_field_with_name(value, [&out](std::string_view name, const auto& field, bool last) {
        append(out, name, field, last);
    });
    out.push_back('}');
    return out;
}

template <typename... Args>
constexpr std::string format(Args&&... args) {
    std::string out{"{"};
    (out.append(args), ...);
    if constexpr (sizeof...(Args) > 0) {
        out.pop_back(); // Remove trailing comma
    }
    out.push_back('}');
    return out;
}

#define SCULK_FORMAT_FIELD(FIELD) std::format("{}: {}", #FIELD, formatter::detail::typeToString(FIELD))

#define SCULK_FORMAT_PACKET(...) formatter::format(__VA_ARGS__);

} // namespace formatter

} // namespace sculk::protocol::inline abi_v975