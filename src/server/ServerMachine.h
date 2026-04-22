#pragma once

#include <ECS.h>
#include <server/ECS/Systems/ServerSystem.h>

#include <atomic>
#include <thread>
#include <chrono>
#include <fmt/core.h>

using namespace ECS;

class ServerMachine {
private:
    std::atomic<bool> running;
    std::thread serverThread;
    const float FIXED_DELTA_TIME = 1 / 1.f;

    void runLoop() {
        World* world = World::createWorld();
        ServerSystem* serverSystem = new ServerSystem();
        world->registerSystem(serverSystem);
        fmt::println("World and systems created in server thread");

        using namespace std::chrono;
        const long long step = static_cast<long long>(FIXED_DELTA_TIME * 1'000'000'000LL);
        auto lastTime = steady_clock::now();
        long long timeSinceLastUpdate = 0;

        while (running) {
            auto currentTime = steady_clock::now();
            long long elapsed = duration_cast<nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            timeSinceLastUpdate += elapsed;

            if (timeSinceLastUpdate < step) {
                long long remain = step - timeSinceLastUpdate;
                if (remain >= 1'000'000LL) {
                    std::this_thread::sleep_for(nanoseconds(remain));
                }
            } else {
                do {
                    world->tick(FIXED_DELTA_TIME);
                    timeSinceLastUpdate -= step;
                } while (timeSinceLastUpdate >= step);
            }
        }

        world->cleanup();
        world->destroyWorld();
        fmt::println("Server thread finished");
    }

public:
    ServerMachine() : running(false) {}
    ~ServerMachine() { stopServer(); }

    void startServer() {
        if (running) return;
        running = true;
        serverThread = std::thread(&ServerMachine::runLoop, this);
        fmt::println("ServerMachine started");
    }

    void stopServer() {
        if (!running) return;
        running = false;
        if (serverThread.joinable()) {
            serverThread.join();
        }
        fmt::println("ServerMachine stopped");
    }
};