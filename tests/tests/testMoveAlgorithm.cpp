#include "tests.hpp"
#include "Atoms/MoveAlgorithm/IMoveAlgorithm.hpp"
#include "Atoms/MoveAlgorithm/Frozen.hpp"
#include "Atoms/MoveAlgorithm/VelocityVerlet.hpp"

using namespace md;

namespace testFrozen
{
    void zeroArguments()
    {
        IMoveAlgorithm* alg = new Frozen();
        auto [position, velocity] = alg->move(Position{}, Vector{}, Vector{}, randomDouble<10, 100>());
        delete alg;

        assert(equal(position, Vector{}));
        assert(equal(velocity, Vector{}));
    }

    void randomInitialPosition()
    {
        IMoveAlgorithm* alg = new Frozen();
        Position initialPosition = randomPosition();
        auto [position, velocity] = alg->move(initialPosition, Vector{}, Vector{}, randomDouble<10, 100>());
        delete alg;

        assert(equal(position, initialPosition));
        assert(equal(velocity, Vector{}));
    }

    void randomVelocity()
    {
        IMoveAlgorithm* alg = new Frozen();
        Vector initialVelocity = randomVector();
        auto [position, velocity] = alg->move(Position{}, initialVelocity, Vector{}, randomDouble<10, 100>());
        delete alg;

        assert(equal(position, Vector{}));
        assert(equal(velocity, Vector{}));
    }

    void randomAcceleration()
    {
        IMoveAlgorithm* alg = new Frozen();
        Vector initialAcceleration= randomVector();
        auto [position, velocity] = alg->move(Position{}, Vector{}, initialAcceleration, randomDouble<10, 100>());
        delete alg;

        assert(equal(position, Vector{}));
        assert(equal(velocity, Vector{}));
    }

    void random()
    {
        IMoveAlgorithm* alg = new Frozen();
        Position initialPosition = randomPosition();
        Vector initialVelocity = randomVector();
        Vector initialAcceleration= randomVector();
        auto [position, velocity] = alg->move(
            initialPosition, initialVelocity, initialAcceleration, randomDouble<10, 100>()
        );
        delete alg;

        assert(equal(position, initialPosition));
        assert(equal(velocity, Vector{}));
    }
}

namespace testVelocityVerlet
{
    void zeroArguments()
    {
        IMoveAlgorithm* alg = new VelocityVerlet();
        auto [position, velocity] = alg->move(Position{}, Vector{}, Vector{}, randomDouble<10, 100>());
        delete alg;

        assert(equal(position, Vector{}));
        assert(equal(velocity, Vector{}));
    }

    void randomInitialPosition()
    {
        IMoveAlgorithm* alg = new VelocityVerlet();
        Position initialPosition = randomPosition();
        auto [position, velocity] = alg->move(initialPosition, Vector{}, Vector{}, randomDouble<10, 100>());
        delete alg;

        assert(equal(position, initialPosition));
        assert(equal(velocity, Vector{}));
    }

    void randomVelocity()
    {
        IMoveAlgorithm* alg = new VelocityVerlet();
        double time = randomDouble<10, 100>();
        Vector initialVelocity= randomVector();
        auto [position, velocity] = alg->move(Position{}, initialVelocity, Vector{}, time);
        delete alg;

        assert(equal(position, initialVelocity * time));
        assert(equal(velocity, initialVelocity));
    }

    void randomAcceleration()
    {
        IMoveAlgorithm* alg = new VelocityVerlet();
        double time = randomDouble<10, 100>();
        Vector initialAcceleration= randomVector();
        auto [position, velocity] = alg->move(Position{}, Vector{}, initialAcceleration, time);
        delete alg;

        assert(equal(position, 0.5 * initialAcceleration * std::pow(time, 2)));
        assert(equal(velocity, initialAcceleration * time));
    }

    void random()
    {
        IMoveAlgorithm* alg = new VelocityVerlet();
        int time = static_cast<int>(randomDouble<100, 1000>());
        Position initialPosition = randomPosition();
        Vector initialVelocity = randomVector();
        Vector initialAcceleration= randomVector();
        Position position = initialPosition;
        Vector velocity = initialVelocity;

        for(int i = 0; i < time; ++i)
            std::tie(position, velocity) = alg->move(position, velocity, initialAcceleration, 1./time);
        delete alg;

        assert(equal(position, initialPosition + initialVelocity + 0.5 * initialAcceleration, 3));
        assert(equal(velocity, initialVelocity + initialAcceleration, 3));
    }
}

void testMoveAlgorithm()
{
    testFrozen::zeroArguments();
    testFrozen::randomInitialPosition();
    testFrozen::randomVelocity();
    testFrozen::randomAcceleration();
    testFrozen::random();

    testVelocityVerlet::zeroArguments();
    testVelocityVerlet::randomInitialPosition();
    testVelocityVerlet::randomVelocity();
    testVelocityVerlet::randomAcceleration();
    testVelocityVerlet::random();
}
