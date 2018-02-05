private const int LED_PIN1 = 18;
private const int LED_PIN2 = 23;
private const int LED_PIN3 = 24;
private const int LED_PIN4 = 25;
private GpioPin pin1, pin2, pin3, pin4;

private int iCounter = 0;

public void Run(IBackgroundTaskInstance taskInstance)
{
    // Need to defer as a background application
    deferral = taskInstance.GetDeferral();
    InitGPIO();
    stopwatch = Stopwatch.StartNew();

    GpioController controller = GpioController.GetDefault();

    timer = ThreadPoolTimer.CreatePeriodicTimer(this.Tick, TimeSpan.FromSeconds(2));

    //You do not need to await this, as your goal is to have this run for the lifetime of the application
    ThreadPool.RunAsync(this.MotorThread, WorkItemPriority.High);

}

// Init IOs - All must be low in initializing state
private void InitGPIO()
{
    pin1 = GpioController.GetDefault().OpenPin(LED_PIN1);
    pin1.Write(GpioPinValue.Low);
    pin1.SetDriveMode(GpioPinDriveMode.Output);
    pin2 = GpioController.GetDefault().OpenPin(LED_PIN2);
    pin2.Write(GpioPinValue.Low);
    pin2.SetDriveMode(GpioPinDriveMode.Output);
    pin3 = GpioController.GetDefault().OpenPin(LED_PIN3);
    pin3.Write(GpioPinValue.Low);
    pin3.SetDriveMode(GpioPinDriveMode.Output);
    pin4 = GpioController.GetDefault().OpenPin(LED_PIN4);
    pin4.Write(GpioPinValue.Low);
    pin4.SetDriveMode(GpioPinDriveMode.Output);

}

// You can change the direction here for every 2 seconds
private void Tick(ThreadPoolTimer timer)
{
    
}

// 
private void MotorThread(IAsyncAction action)
{
    //This motor thread runs on a high priority task and loops forever to pulse the motor
    while (true)
    {
        switch (iCounter)
        {
            // 8 stats stepping
            case 0:
                pin1.Write(GpioPinValue.Low);
                pin2.Write(GpioPinValue.Low);
                pin3.Write(GpioPinValue.Low);
                pin4.Write(GpioPinValue.High);
                break;
            case 1:
                pin1.Write(GpioPinValue.Low);
                pin2.Write(GpioPinValue.Low);
                pin3.Write(GpioPinValue.High);
                pin4.Write(GpioPinValue.High);
                break;
            case 2:
                pin1.Write(GpioPinValue.Low);
                pin2.Write(GpioPinValue.Low);
                pin3.Write(GpioPinValue.High);
                pin4.Write(GpioPinValue.Low);
                break;
            case 3:
                pin1.Write(GpioPinValue.Low);
                pin2.Write(GpioPinValue.High);
                pin3.Write(GpioPinValue.High);
                pin4.Write(GpioPinValue.Low);
                break;
            case 4:
                pin1.Write(GpioPinValue.Low);
                pin2.Write(GpioPinValue.High);
                pin3.Write(GpioPinValue.Low);
                pin4.Write(GpioPinValue.Low);
                break;
            case 5:
                pin1.Write(GpioPinValue.High);
                pin2.Write(GpioPinValue.High);
                pin3.Write(GpioPinValue.Low);
                pin4.Write(GpioPinValue.Low);
                break;
            case 6:
                pin1.Write(GpioPinValue.High);
                pin2.Write(GpioPinValue.Low);
                pin3.Write(GpioPinValue.Low);
                pin4.Write(GpioPinValue.Low);
                break;
            case 7:
                pin1.Write(GpioPinValue.High);
                pin2.Write(GpioPinValue.Low);
                pin3.Write(GpioPinValue.Low);
                pin4.Write(GpioPinValue.High);
                break;
            default: break;
        }
        if (iCounter == 7) iCounter = 0;
        else iCounter++;
        //Use the wait helper method to wait for the length of the pulse
        Wait(1);
    }
}

//A synchronous wait is used to avoid yielding the thread 
//This method calculates the number of CPU ticks will elapse in the specified time and spins
//in a loop until that threshold is hit. This allows for very precise timing.
private void Wait(double milliseconds)
{
    long initialTick = stopwatch.ElapsedTicks;
    long initialElapsed = stopwatch.ElapsedMilliseconds;
    double desiredTicks = milliseconds / 1000.0 * Stopwatch.Frequency;
    double finalTick = initialTick + desiredTicks;
    while (stopwatch.ElapsedTicks < finalTick)
    {

    }
}
