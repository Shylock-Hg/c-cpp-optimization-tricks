#include <cstdint>
#include <cstdio>
#include <cstddef>
#include <iostream>
#include <type_traits>

// copy from facebook folly

namespace detail {

template <typename T>
struct DoNotOptimizeAwayNeedsIndirect {
  using Decayed = typename std::decay<T>::type;

  // First two constraints ensure it can be an "r" operand.
  // std::is_pointer check is because callers seem to expect that
  // doNotOptimizeAway(&x) is equivalent to doNotOptimizeAway(x).
  constexpr static bool value = !std::is_trivially_copyable<Decayed>::value ||
      sizeof(Decayed) > sizeof(long) || std::is_pointer<Decayed>::value;
};

} // namespace detail

template <typename T>
auto doNotOptimizeAway(const T& datum) -> typename std::enable_if<
    !detail::DoNotOptimizeAwayNeedsIndirect<T>::value>::type {
  // The "r" constraint forces the compiler to make datum available
  // in a register to the asm block, which means that it must have
  // computed/loaded it.  We use this path for things that are <=
  // sizeof(long) (they have to fit), trivial (otherwise the compiler
  // doesn't want to put them in a register), and not a pointer (because
  // doNotOptimizeAway(&foo) would otherwise be a foot gun that didn't
  // necessarily compute foo).
  //
  // An earlier version of this method had a more permissive input operand
  // constraint, but that caused unnecessary variation between clang and
  // gcc benchmarks.
  asm volatile("" ::"r"(datum));
}

template <typename T>
auto doNotOptimizeAway(const T& datum) -> typename std::enable_if<
    detail::DoNotOptimizeAwayNeedsIndirect<T>::value>::type {
  // This version of doNotOptimizeAway tells the compiler that the asm
  // block will read datum from memory, and that in addition it might read
  // or write from any memory location.  If the memory clobber could be
  // separated into input and output that would be preferrable.
  asm volatile("" ::"m"(datum) : "memory");
}


/// These will be compile to vectorized instructions(e.g. SSE/AVX), which unroll the loop and
/// parallel executing.
/// For more infomation, could check the auto-vectorized manual of clang in
/// https://llvm.org/docs/Vectorizers.html#auto-vectorization-in-llvm
int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int c[8];
    for (int i = 0; i < 8; ++i) {
        c[i] = a[i] + b[i];
    }
    doNotOptimizeAway(c);
    return 0;
}
