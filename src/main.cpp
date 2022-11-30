/**
 * @file main.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief This file is the enterance point of the application.
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 */

#include <Arduino.h>
#include <vector>
#include <list>

#define TEST_SIZE 1000

std::vector<int> testVector;
std::list<int> testList;
int *testArray;

int testValue = 0;

unsigned long timeMicroSecFirst = 0;
unsigned long timeMicroSecLast = 0;

unsigned long timeIntervalVectorFill = 0;
unsigned long timeIntervalArrayFill = 0;
unsigned long timeIntervalListFill = 0;

unsigned long timeIntervalVectorAccess = 0;
unsigned long timeIntervalArrayAccess = 0;
unsigned long timeIntervalListAccess = 0;

unsigned long timeIntervalVectorInsert = 0;
unsigned long timeIntervalArrayInsert = 0;
unsigned long timeIntervalListInsert = 0;

/**
 * @brief Setup function that works only when the ECU is restarted.
 */
void setup()
{
    Serial.begin(9600); /* Set the serial communication spped for the MCU. */

    /**
     * @note Test time requirements for filling different type of storages.
     */

    timeMicroSecFirst = micros();       /* Get the time before filling the vector. */
    for (int i = 0; i < TEST_SIZE; i++) /* Fill the test vector. */
    {
        testVector.push_back(i);
    }
    timeMicroSecLast = micros();
    timeIntervalVectorFill = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to fill the vector. */

    timeMicroSecFirst = micros();                       /* Get the time before filling the array. */
    testArray = (int *)malloc(sizeof(int) * TEST_SIZE); /* C style memory allocation. */
    for (int i = 0; i < TEST_SIZE; i++)                 /* Fill the test array. */
    {
        testArray[i] = i;
    }
    timeMicroSecLast = micros();
    timeIntervalArrayFill = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to fill the array. */

    timeMicroSecFirst = micros();       /* Get the time before filling the list. */
    for (int i = 0; i < TEST_SIZE; i++) /* Fill the test list. */
    {
        testList.push_back(i);
    }
    timeMicroSecLast = micros();
    timeIntervalListFill = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to fill the list. */

    /**
     * @note Test time requirements of access time for different type of storages.
     */

    timeMicroSecFirst = micros();       /* Get the time before accessing the vector. */
    for (int i = 0; i < TEST_SIZE; i++) /* Get the elements of the test vector. */
    {
        testValue = testVector[i];
    }
    timeMicroSecLast = micros();
    timeIntervalVectorAccess = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to access the vector. */

    timeMicroSecFirst = micros();       /* Get the time before accessing the array. */
    for (int i = 0; i < TEST_SIZE; i++) /* Get the elements of the test array. */
    {
        testValue = testArray[i];
    }
    timeMicroSecLast = micros();
    timeIntervalArrayAccess = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to access the array. */

    timeMicroSecFirst = micros();                                                    /* Get the time before accessing the list. */
    for (std::list<int>::iterator it = testList.begin(); it != testList.end(); it++) /* Get the elements of the test list. */
    {
        testValue = *it;
    }
    timeMicroSecLast = micros();
    timeIntervalListAccess = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to access the list. */

    /**
     * @note Test time requirements of inserting for different type of storages.
     */

    timeMicroSecFirst = micros();       /* Get the time before inserting into the vector. */
    for (int i = 0; i < TEST_SIZE; i++) /* Insert the elements into the test vector. */
    {
        std::vector<int>::iterator itVec = testVector.begin() + TEST_SIZE / 2;
        testVector.insert(itVec, i);
    }
    timeMicroSecLast = micros();
    timeIntervalVectorInsert = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to insert into the vector. */

    timeMicroSecFirst = micros();       /* Get the time before inserting into the list. */
    for (int i = 0; i < TEST_SIZE; i++) /* Insert the elements into to the test list. */
    {
        std::list<int>::iterator itList = testList.begin();
        std::advance(itList, TEST_SIZE / 2);
        testList.insert(itList, i);
    }
    timeMicroSecLast = micros();
    timeIntervalListInsert = timeMicroSecLast - timeMicroSecFirst; /* Calculate the eclapsed time to insert into the list. */

    /**
     * @note Print the results.
     */

    Serial.println("Vector filling time (uS) : " + String(timeIntervalVectorFill));
    Serial.println("Array filling time (uS) : " + String(timeIntervalArrayFill));
    Serial.println("List filling time (uS) : " + String(timeIntervalListFill));
    Serial.println("Vector access time (uS) : " + String(timeIntervalVectorAccess));
    Serial.println("Array access time (uS) : " + String(timeIntervalArrayAccess));
    Serial.println("List access time (uS) : " + String(timeIntervalListAccess));
    Serial.println("Vector insert time (uS) : " + String(timeIntervalVectorInsert));
    Serial.println("List insert time (uS) : " + String(timeIntervalListInsert));

    /**
     * @note Here is an example result of calculations:
     *
     * Vector filling time (uS) : 485
     * Array filling time (uS) : 28
     * List filling time (uS) : 12474
     *
     * Vector access time (uS) : 21
     * Array access time (uS) : 17
     * List access time (uS) : 38
     *
     * Vector insert time (uS) : 168518
     * List insert time (uS) : 30847
     */
}

/**
 * @brief Application loop function.
 */
void loop()
{
    delay(5000);
}