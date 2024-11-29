#ifndef _NEW_KM_H
#define _NEW_KM_H

#include "stdint.h"


/*---------------------------------------------------- NEW KM -----------------------------------------*/

/**
 * @brief Slowly moves the king to the left stopper.
 *
 * This function moves the king to the left stopper from any position and
 * handles various error conditions, such as the king being already on a stopper
 * or not being in a stopper.
 *
 * @return An error code indicating the result of the operation.
 */
enum ErrorCode kingCalibrateToLeft(void);

/**
 * @brief Moves the king from side to side.
 *
 * This function moves the king from stopper to stopper in the specified direction (left or right) and
 * handles various error conditions, such as the king being already on a stopper
 * or not being in a stopper.
 *
 * @param dir The direction to move the king (0 for left, 1 for right).
 *
* @return An error code indicating the result of the operation
 */
enum ErrorCode kingFromSideToSide(uint8_t dir);

/**
 * @brief Moves the king from left stopper to some position.
 *
 * This function moves the king from left stopper to some position and
 * handles various error conditions, such as the king being already on a stopper
 * or not being in a stopper.
 *
 * @param steps The number of steps to move the king.
 *
 * @return An error code indicating the result of the operation
 */
enum ErrorCode kingFromLeftToPos(uint32_t steps);

/**
 * @brief Moves the king from some position to stopper.
 *
 * This function moves the king from some position to stopper and
 * handles various error conditions, such as the king being already on a stopper
 * or not being in a stopper.
 *
 * @param timeout The number of steps to move the king.
 * @param dir The direction of the king. 0 = left, 1 = right
 *
 * @return An error code indicating the result of the operation
 */
enum ErrorCode kingFromPosToStop(uint32_t timeout, uint8_t dir);

/**
 * @brief Calibrate pawn to stopper
 *
 * This function moves the pawn to the stopper from any position and
 * handles various error conditions, such as the pawn being already on a stopper
 * or not being in a stopper.
 *
 * @return An error code indicating the result of the operation.
 */
enum ErrorCode PawnCalibrationCCW(void);

/**
 * @brief Drop pawn
 *
 * This function drops the product from the pawn.
 *
 * @return An error code indicating the result of the operation.
 */
enum ErrorCode DropPawnFunc(void);

/*---------------------------------------------------- END NEW KM ---------------------------------------*/

#endif  //_NEW_KM_H
