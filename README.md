# self_balance_robot

Self-balancing robot: Arduino Uno + MPU6050 + L298N + two geared DC motors.

## Wiring

| Signal | Pin |
|---|---|
| Motor 1 enable (PWM) | 9 |
| Motor 1 forward / backward | 11 / 10 |
| Motor 2 enable (PWM) | 3 |
| Motor 2 forward / backward | 6 / 5 |
| MPU6050 | SDA = A4, SCL = A5 |

> Pins 5, 6, 9, 10, 11 and 3 are all on the Uno's timers. Do not add another
> `analogWrite()` on pin 5/6 (Timer0) — it would disturb `millis()` timing.

## Build and upload

```bash
pio run -t upload
pio device monitor -b 115200
```

Keep the robot completely still for ~5 seconds after reset: that is the gyro
calibration.

## How it works

```
MPU6050 -> complementary filter -> angle (deg)
        -> gyro X rate (deg/s)
                 |
        PID on angle error, D taken from the gyro rate
                 |
        MotorDrive(-255..255) -> L298N
```

* `GyroUpdate()` is called exactly once per loop; the angle and the rate are
  then cached, so the loop never blocks on Serial inside the control path.
* The controller runs every 10 ms (100 Hz).
* The D term uses the raw gyro rate instead of differentiating the angle.
  Same effect, far less noise.
* `MotorDrive()` compensates the motor dead zone: any command above
  `STOP_BAND` is boosted to at least `MIN_PWM`, so small corrections actually
  move the wheels instead of buzzing.
* Safety: if the robot leans more than `FALL_LIMIT_DEG` from the setpoint the
  motors are cut immediately. They only restart after the robot has been held
  within `REARM_LIMIT_DEG` of the setpoint for `REARM_HOLD_MS`.

## Tuning

All tuning values are at the top of `src/main.cpp`.

1. **Find the setpoint.**
   Upload, open the Serial Monitor (115200) and hold the robot perfectly
   upright. Read `angle=...` and put that number into `SETPOINT`.
   It is negative in this build (`-70.0`), which is normal: it only depends on
   how the MPU6050 is mounted.

2. **Set `KI = 0`, `KD = 0`, `KP = 5`.**
   Hold the robot upright and let go. Increase `KP` in steps until the robot
   can hold itself but oscillates back and forth. That is the right ballpark.

3. **Raise `KD` in small steps** (0.2 at a time) until the oscillation is
   damped out. If the robot buzzes or shakes, `KD` is too high.

4. **Increase `KP` slightly** and fine-tune `KD`. Stop when it is stable but
   still reacts quickly to a push.

5. **Leave `KI` at 0.** Only add a very small value (0.001 – 0.01) if the
   robot always balances at a slight lean. `KI` makes the robot slowly drive
   to correct the lean, so too much of it causes drifting.

### Direction is wrong?

If the robot immediately drives away from the balance point and falls, the
correction direction is inverted. Fix it by either:

* swapping the two wires of **both** motors, or
* negating `KP` and `KD` in `src/main.cpp`.

If it spins instead of driving straight, set `INVERT_MOTOR1` or
`INVERT_MOTOR2` to `true` in `src/motor.cpp`.

## Troubleshooting

| Problem | Try |
|---|---|
| Serial shows garbage | Baud rate must be 115200 |
| `angle` never changes | Check I2C wiring (A4/A5); if it still fails, remove `Wire.setClock(400000)` |
| Angle drifts slowly while still | Re-run setup without touching the robot during calibration |
| Motors buzz but do not turn | Lower `MIN_PWM` in `motor.cpp` |
| Robot twitches at balance | Raise `STOP_BAND`, or lower `KD` |
| Robot falls immediately | `SETPOINT` is wrong, or the direction is inverted |

## Files

| File | Purpose |
|---|---|
| `src/main.cpp` | Tuning values, control loop, safety, telemetry |
| `src/gyro.*` | MPU6050 init, calibration, angle and rate |
| `src/motor.*` | L298N control and dead-zone compensation |
| `src/Pid.*` | PID controller with anti-windup |
| `backup_src/` | Original version of the code |
