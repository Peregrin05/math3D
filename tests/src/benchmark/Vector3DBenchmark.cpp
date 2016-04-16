#include <benchmark/benchmark_api.h>
#include <string>
#include <Vector3D.h>

using namespace flash::math;

static void vec_addition(benchmark::State& state) {
    Vector3D v1 = {1, 0.23, 3}, v2 = {0.342342, 2.234, -1.10001414f};
    while (state.KeepRunning())
        Vector3D result = v1 + v2;
}
BENCHMARK(vec_addition);

static void vec_dotProduct(benchmark::State& state) {
    Vector3D v1 = {1, 0.23, 3}, v2 = {0.342342, 2.234, -1.10001414f};
    while (state.KeepRunning())
        Vector3D result = v1 * v2;
}
BENCHMARK(vec_dotProduct);