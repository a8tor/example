#ifndef _MOT_Z_H
#define _MOT_Z_H

/*--------------------------------------    Mot Z   Start  -------------------------------------*/

/**
 * @brief Moves the water from some position to down stopper.
 *
 * This function moves the water from some position to down stopper and
 * handles various error conditions, such as the water being already on a stopper
 * or not being in a stopper.
 *
 * @return An error code indicating the result of the operation
 */
enum ErrorCode staZCal(void);

/**
 * @brief Moves the water from down to up stopper.
 *
 * This function moves the water from down position to up stopper and
 * handles various error conditions, such as the water being already on a stopper
 * or not being in a stopper.
 * Moves fast first ~6000 steps, then slow ~3000 steps
 *
 * @return An error code indicating the result of the operation
 */
enum ErrorCode staZTUp(void);

/**
 * @brief Moves the water from up to down stopper.
 *
 * This function moves the water from up position to down stopper and
 * handles various error conditions, such as the water being already on a stopper
 * or not being in a stopper.
 *
 * @return An error code indicating the result of the operation
 */
enum ErrorCode staZTDown(void);

/**
 * @brief Moves the water up to 50 steps.
 *
 * This function moves the water from any position to up
 *
 * @return An error code indicating the result of the operation
 */
enum ErrorCode staZUpStp(void);

/**
 * @brief Moves the water down to 50 steps.
 *
 * This function moves the water from any position to down
 *
 * @return An error code indicating the result of the operation
 */
enum ErrorCode staZDownStp(void);

/*----------------------------------------    Mot Z   End  -------------------------------------*/

#endif  //_MOT_Z_H
