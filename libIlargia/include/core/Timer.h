#ifndef ILARGIA_TIMER_H
#define ILARGIA_TIMER_H

namespace Ilargia {

    class Timer {
        double _currentTime, _pausedTime, _newTime, _frameTime, _accumulator, _alpha = 0.0;
        bool _started, _paused = false;
        int _steps = 60.0;
        double _timeStep;
        int _numStep = 0;

    public:
        Timer() {  _timeStep =1.0/ _steps;}

        Timer(int steps) : _steps(steps) { _timeStep =1.0/ _steps;}

        void start() {
            _started = true;
            _paused = false;
            _currentTime = getSecondsTime();
            _accumulator = 0.0;
        }

        void stop() {
            _started = false;
            _paused = false;
        }

        void pause() {
            if (_started && !_paused) {
                _paused = true;
                _pausedTime = getSecondsTime() - _currentTime;
            }
        }

        void unpause() {
            if (_paused) {
                _paused = false;
                _currentTime = getSecondsTime() - _pausedTime;
                _pausedTime = 0;
            }
        }

        double step() {
            if (_started) {
                if (_paused)
                    return 0.0;
                else {
                    _newTime = getSecondsTime();
                    _frameTime = _newTime - _currentTime;
                    if (_frameTime > 0.25)
                        _frameTime = 0.25;
                    _currentTime = _newTime;

                    _accumulator += _frameTime;

                    if (_accumulator >= _timeStep) {
                        _accumulator -= _timeStep;
                        _alpha = _accumulator / _timeStep;
                        _numStep++;
                        if(_numStep>59) _numStep=1;
                        return _timeStep;
                    }

                }
            }
            return 0.0;
        }

        bool started() const {
            return _started;
        }

        bool paused() const {
            return _paused;
        }

        int numStep() const {
            return _numStep;
        }



        virtual double getSecondsTime() { 0;}


    };
}
#endif //ILARGIA_TIMER_H
