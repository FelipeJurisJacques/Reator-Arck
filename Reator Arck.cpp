int LED = 11;
int BUTTON = 8;
int STATE = 0;
int MIN = 0;
int MAX = 0;
int _INACTIVE = 0;

void setup() {  
    pinMode(BUTTON, INPUT);
    _INACTIVE = 10;
}

void loop() {
    if (STATE == 1) {
        // ON
        for (int i = MIN; i < MAX; i += 5) {
            analogWrite(LED, i);
            bright(1);
            delay(60);
        }
        for (int i = MAX; i > MIN; i -= 5) {
            analogWrite(LED, i);
            bright(1);
            delay(60);
        }
        if (MAX == 0) {
            STATE = 0;
        }
    } else {
        delay(1000);
        analogWrite(LED, 0);
        if (isActive()) {
            // START
            int wait = 500;
            for (MAX = 0; MAX < 255; MAX++)  {
                if (MAX > 170) {
                    MIN++;
                }
                wait = wait > 1 ? wait / 1.05 : 1;
                analogWrite(LED, MAX);
                delay(wait > 100 ? 100 : wait);
                analogWrite(LED, MIN);
                delay(wait);
            }
            STATE = 1;
            MIN = 85;
            MAX = 255;
            if (isActive()) {
                for (int i = MAX; i > MIN; i -= 5) {
                    analogWrite(LED, i);
                    delay(60);
                }
            }
        }
    }
}

void bright(int step)
{
    if (isActive()) {
        if (MAX < 255) {
            MAX += step;
            if (MAX > 170) {
                MIN += step;
            }
        }
    } else if (MAX > 0) {
        MAX -= step;
        if (MAX < 170) {
            MIN -= step;
        }
    }
    if (MAX > 255 || MIN > 170) {
        MAX = 255;
        MIN = 170;
    } else if (MAX < 0 || MIN < 0) {
        MAX = 0;
        MIN = 0;
    }
}

bool isActive()
{
    float read = analogRead(A0);
    if (read > 512.0) {
        _INACTIVE = 0;
    } else {
        _INACTIVE++;
    }
    return _INACTIVE < 5;
}