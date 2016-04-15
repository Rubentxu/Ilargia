#ifndef ILARGIA_TIMER_H
#define ILARGIA_TIMER_H

namespace Ilargia {

    class Timer {
        double currentTime, pausedTicks, newTime, frameTime, accumulator, alpha = 0.0;
        bool started, paused = false;
        double step = 1.0 / 60.0;

    public:
        Timer(double step) : step(step) { }

        void Start() {
            started = true;
            paused = false;
            currentTime = getTime();
            accumulator = 0.0;
        }

        void Stop() {
            started = false;
            paused = false;
        }

        void Pause() {
            if (started && !paused) {
                paused = true;
                pausedTicks = getTime() - currentTime;
            }
        }

        void Unpause() {
            if (paused) {
                paused = false;
                currentTime = getTime() - pausedTicks;
                pausedTicks = 0;
            }
        }

        bool tick() {
            if (started) {
                if (paused)
                    return false;
                else {
                    newTime = getTime();
                    frameTime = newTime - currentTime;
                    if (frameTime > 0.25)
                        frameTime = 0.25;
                    currentTime = newTime;

                    accumulator += frameTime;

                    if (accumulator >= step) {
                        accumulator -= step;
                        alpha = accumulator / step;
                        return true;
                    }

                }
            }
            return false;
        }

        bool Started() const {
            return started;
        }

        bool Paused() const {
            return paused;
        }

        double Step() const {
            return step;
        }

        virtual double getTime() { 0;}


    };
}
#endif //ILARGIA_TIMER_H
