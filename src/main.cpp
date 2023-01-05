/**
 * main.c
 *
 * Author: Michael Stegeman
 * Date: 2/25/08
 *
 * Description: ASCII art fireworks demo
 */

#include "Firework.h"
#include <chrono>
#include <mutex>
#include <ncurses.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<float, std::milli> DurationMs;

struct ThreadArgs {
    int mThreadId;
    Particle* mParticles;
    const size_t mkSize = 200;
    bool mStopFlag = false;
    std::mutex mFlagMutex;
    // TBarrier* mBarrier;
};

/**
 * initializes necessary ncurses attributes
 */
void ncursesInit() {
    WINDOW* window = initscr(); // initialize screen
    noecho();                   // don't display typed characters
    cbreak();                   // don't wait until RETURN is pressed
    nodelay(window, TRUE);      // don't wait for key press
    curs_set(0);                // make cursor invisible
    start_color();              // start color in terminal
    init_pair(1, 7, 0);         // White on black
    init_pair(2, 6, 0);         // Cyan on black
    init_pair(3, 5, 0);         // Magenta on black
    init_pair(4, 4, 0);         // Blue on black
    init_pair(5, 3, 0);         // Yellow on black
    init_pair(6, 2, 0);         // Green on black
    init_pair(7, 1, 0);         // Red on black
}

// void threadUpdateParticles(void* threadArgs) {
//     int threadId = static_cast<ThreadArgs*>(threadArgs)->mThreadId;
//     const size_t& kSize = static_cast<ThreadArgs*>(threadArgs)->mkSize;
//     bool& stop = static_cast<ThreadArgs*>(threadArgs)->mStopFlag;
//     std::mutex& flagMutex =
//     static_cast<ThreadArgs*>(threadArgs)->mFlagMutex; Particle* particles =
//     static_cast<ThreadArgs*>(threadArgs)->mParticles;

//     while (true) {
//         {
//             std::lock_guard<std::mutex> lock(flagMutex);
//             if (threadId == 0 && getch() != 'q') {
//                 stop = true;
//             }
//             if (stop) {
//                 return;
//             }
//         }

//         if (particles[0].mLife < 1.21 && particles[0].mLife > 1.19) {
//             // reinitialize second array at 3/4 life of first
//             particleInit(particles, kSize);
//         }
//         // update all particles
//         particleUpdate(particles, 0.01, kSize);
//         // draw all particles to screen
//         particleDraw(particles, kSize);
//     }

//     delete[] particles;
//     particles = nullptr;
// }

int main() {
    constexpr int INTERVAL_MS = 33; // 30 FPS
    auto lastFrameMs = Clock::now();
    auto currentFrameMs = Clock::now();
    // constexpr size_t SIZE = 200;
    // constexpr int NUM_THREADS = 2;

    ncursesInit();
    srand((unsigned)time(NULL));

    // reserve memory for particle array
    // Particle* p = (Particle*)calloc(sizeof(Particle), SIZE);
    // Particle* q = (Particle*)calloc(sizeof(Particle), SIZE);
    // Particle* r = (Particle*)calloc(sizeof(Particle), SIZE);
    // Particle* s = (Particle*)calloc(sizeof(Particle), SIZE);
    // Particle* p = new Particle[SIZE];

    // // initialize particle array
    // particleInit(p, SIZE);
    // particleInit(q, SIZE);
    // particleInit(r, SIZE);
    // particleInit(s, SIZE);

    // std::vector<std::thread> thread_pool;
    // for (int i = 0; i < num_threads; i++) {
    //     thread_pool.push_back(
    //       std::thread(&Function_pool::infinite_loop_func, &func_pool));
    // }

    // ThreadArgs* args = new ThreadArgs{};
    // args->mBarrier = new TBarrier(NUM_THREADS + 1);
    // check for user input to quit program
    std::array<Firework, 5> fireworks;
    for (auto& firework : fireworks) {
        firework.init();
    }
    while (getch() != 'q') {
        // if (p[0].mLife < 1.21 && p[0].mLife > 1.19) {
        //     // reinitialize second array at 3/4 life of first
        //     particleInit(q, SIZE);
        // } else if (p[0].mLife < 0.81 && p[0].mLife > 0.79) {
        //     // reinitialize third array at 1/2 life of first
        //     particleInit(r, SIZE);
        // } else if (p[0].mLife < 0.41 && p[0].mLife > 0.39) {
        //     // reinitialize fourth array at 1/4 life of first
        //     particleInit(s, SIZE);
        // } else if (p[0].mLife < 0.01) {
        //     // check for end of life and reinitialize array if dead
        //     particleInit(p, SIZE);
        // }

        // erase screen
        erase();

        // update all particles
        // particleUpdate(p, 0.01, SIZE);
        // particleUpdate(q, 0.01, SIZE);
        // particleUpdate(r, 0.01, SIZE);
        // particleUpdate(s, 0.01, SIZE);

        // // draw all particles to screen
        // particleDraw(p, SIZE);
        // particleDraw(q, SIZE);
        // particleDraw(r, SIZE);
        // particleDraw(s, SIZE);
        for (auto& firework : fireworks) {
            if (firework.lifeInPercentage() < 0.0) {
                if( rand() % 100 != 0) {
                    continue;
                }
                firework.init();
            }
            firework.update(INTERVAL_MS);
            firework.draw();
        }

        // std::thread(threadRenderFirework, args);

        // draw particles to screen
        refresh();
        currentFrameMs = Clock::now();

        // std::this_thread::sleep_for(std::chrono::milliseconds(x));
        // wait a bit
        std::this_thread::sleep_for(DurationMs(INTERVAL_MS) -
                                    (currentFrameMs - lastFrameMs));
        lastFrameMs = currentFrameMs;
        // std::cout << (currentFrameMs - lastFrameMs).count() << "ms passed"
        // << std::endl; nanosleep(&INTERVAL, NULL);
    }

    // {
    //     std::lock_guard<std::mutex> lock(args->mFlagMutex);
    //     args->mStopFlag = true;
    // }

    // free(p);
    // p = NULL;
    // free(q);
    // q = NULL;
    // free(r);
    // r = NULL;
    // free(s);
    // s = NULL;

    endwin();

    return 0;
}
