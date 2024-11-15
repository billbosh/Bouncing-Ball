#include <random>

float randomFloatInRange (float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    float result = dist(gen);
    return result;
}
