#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>  // ファイル出力

struct Particle {
    double position;  // パーティクルの位置
    double weight;    // パーティクルの重み
};

class MCL {
public:
    MCL(int num_particles, double initial_position)
        : num_particles(num_particles), initial_position(initial_position) {
        particles.resize(num_particles);
        for (auto &particle : particles) {
            particle.position = initial_position;
            particle.weight = 1.0 / num_particles;
        }
    }

    void sensorUpdate(double sensor_value) {
        double total_weight = 0.0;
        for (auto &particle : particles) {
            double error = std::abs(particle.position - sensor_value);
            double weight = std::exp(-0.5 * std::pow(error / 1.5, 2));
            particle.weight = weight;
            total_weight += weight;
        }

        if (total_weight > 0) {
            for (auto &particle : particles) {
                particle.weight /= total_weight;
            }
        }
    }

    void resampleParticles() {
        double total_weight = 0;
        for (const auto &particle : particles) {
            total_weight += particle.weight;
        }

        if (total_weight == 0) {
            std::cout << "Warning: Total weight is zero, resampling skipped." << std::endl;
            return;
        }

        std::vector<Particle> resampled_particles;
        for (int i = 0; i < particles.size(); ++i) {
            double rand_weight = rand() / double(RAND_MAX) * total_weight;
            double cumulative_weight = 0;
            for (const auto &particle : particles) {
                cumulative_weight += particle.weight;
                if (cumulative_weight >= rand_weight) {
                    resampled_particles.push_back(particle);
                    break;
                }
            }
        }

        particles = resampled_particles;
    }

    void moveParticles() {
        for (auto &particle : particles) {
            particle.position += rand() % 3 - 1;  // -1, 0, 1 のランダムな移動
        }
    }

    void runSimulation(int iterations, double sensor_value) {
        std::ofstream file("particle_positions.csv");
        file << "Iteration,Position\n";

        for (int i = 0; i < iterations; ++i) {
            sensorUpdate(sensor_value);
            resampleParticles();
            moveParticles();

            for (const auto &particle : particles) {
                file << i + 1 << "," << particle.position << "\n";
            }
        }

        file.close();
    }

private:
    int num_particles;
    double initial_position;
    std::vector<Particle> particles;
};

int main() {
    MCL mcl(100, 0);
    double sensor_value = 20;
    mcl.runSimulation(100, sensor_value);

    return 0;
}
