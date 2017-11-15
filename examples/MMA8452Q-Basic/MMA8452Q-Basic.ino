// 使用MMA8452库初始化加速度计并获取加速度值

/* 接线提示：
Hardware hookup:
  Board ---------------      MMA8452Q
  3.3V  ---------------     3.3V
  GND   ---------------     GND
  SDA () --\/330 Ohm\/--    SDA
  SCL () --\/330 Ohm\/--    SCL

MMA8452Q最大电压为3.3V，需要在SDA和SCL上加上电阻。
*/

#include <MMA8452.h>

void printAccels();
void printCalculatedAccels();
void printOrientation();

// 定义MMA8452Q变量
MMA8452Q accel;

void setup()
{
    Serial.begin(115200);
    Serial.println("MMA8452Q Test Code!");

    // 初始化MMA8451Q传感器有多种方法：
    //  1.默认初始化。初始化加速度计的范围+/-2g，输出速率 800 Hz（最快速度）.
    accel.init();
    //  2. 初始化带范围参数。范围参数包括SCALE_2G, SCALE_4G, or SCALE_8G
    //     分别设定的范围为+/-2g，+/-4g，+/-8g
    //accel.init(SCALE_4G);
    //  3. 初始化带范围参数和输出速率。速率参数包括ODR_800, ODR_400, ODR_200,
    //      ODR_100, ODR_50, ODR_12,ODR_6, or ODR_1.
    //     分别设定的频率为 800, 400, 200, 100, 50, 12.5, 6.25, or 1.56 Hz.
    //accel.init(SCALE_8G, ODR_6);
}

void loop()
{
    // 等待传感器数据的到来
    if (accel.available())
    {
        // 读取传感器数据
        accel.read();
        // accel.read()会更新两个变量集。
        // * 整型x, y, z，存储12位未处理的值。
        // * 浮点型cx, cy, and cz，存储从未处理的值计算得到的加速度值，单位为g。
        printCalculatedAccels();  // 输出计算得到的加速度值
        //printAccels();          // 输出未处理的加速度值

        printOrientation();  // 输出传感器的朝向
        Serial.println(); // 输出新行
    }
}


// 输出未处理的加速度值
void printAccels()
{
    Serial.print(accel.x, 3);
    Serial.print("\t");
    Serial.print(accel.y, 3);
    Serial.print("\t");
    Serial.print(accel.z, 3);
    Serial.print("\t");
}

// 输出计算得到的加速度值
void printCalculatedAccels()
{
    Serial.print(accel.cx, 3);
    Serial.print("\t");
    Serial.print(accel.cy, 3);
    Serial.print("\t");
    Serial.print(accel.cz, 3);
    Serial.print("\t");
}

// 输出传感器的朝向，朝向包括PORTRAIT_U, PORTRAIT_D, LANDSCAPE_R, LANDSCAPE_L或者LOCKOUT.
void printOrientation()
{
    byte pl = accel.readPL();
    switch (pl)
    {
        case PORTRAIT_U:
            Serial.print("Portrait Up");
            break;
        case PORTRAIT_D:
            Serial.print("Portrait Down");
            break;
        case LANDSCAPE_R:
            Serial.print("Landscape Right");
            break;
        case LANDSCAPE_L:
            Serial.print("Landscape Left");
            break;
        case LOCKOUT:
            Serial.print("Flat");
            break;
    }
}
