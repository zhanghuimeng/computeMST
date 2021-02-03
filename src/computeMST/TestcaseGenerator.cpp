#include "TestcaseGenerator.h"

#include <vector>
#include <ctime>
#include <cmath>
#include <random>

#include "Graph2D.h"
#include "Settings.h"

int cmst::randomInt(int a, int b)
{
    if (a > b) std::swap(a, b);

    static std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(a, b);

    // std::default_random_engine rng(std::random_device{}());
    // std::uniform_int_distribution<int> dist(a, b);

    // std::cout << a << ' ' << b << ' ' << dist(rng) << std::endl;

    // for (int i = 0; i < 10; i++) std::cout << dist(rng) << std::endl;
    return dist(rng);
}

double cmst::randomDouble(double a, double b)
{
    if (a > b) std::swap(a, b);

    static std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> dist(a, b);

    // std::default_random_engine rng(std::random_device{}());
    // rng.reseed();
    // std::uniform_real_distribution<double> dist(a, b);

    // std::cout << dist(rng) << std::endl;
    return dist(rng);
}

std::vector<cmst::Point2D> cmst::TestcaseGenerator(int num_lower_bound/* = 100*/, int num_upper_bound/* = 500*/,
                              double x_upper_bound/* = MAX_X*/, double y_upper_bound/* = MAX_Y*/)
{
    // srand(time(NULL));
    int numberPoints = randomInt(num_lower_bound, num_upper_bound);

    #ifdef DEBUG
    debugout << "Generating " << numberPoints << " random points" << std::endl;
    #endif // DEBUG

    std::vector<cmst::Point2D> points;
    for(int i = 0; i < numberPoints; i++)
        points.push_back(cmst::Point2D(randomDouble(0.0, x_upper_bound), randomDouble(0.0, y_upper_bound)));

    // delete the same points
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());

    while (points.size() < numberPoints)
    {
        cmst::Point2D p( randomDouble(0.0, x_upper_bound), randomDouble(0.0, y_upper_bound) );
        if (std::lower_bound(points.begin(), points.end(), p) == points.end())
        {
            points.push_back(p);
            std::sort(points.begin(), points.end());
        }
    }

    return points;
}

