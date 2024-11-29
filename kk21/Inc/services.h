#ifndef _SERVICES_H
#define _SERVICES_H

#include "stdint.h"
#include "stm32f7xx_hal_gpio.h"

/*---------------------------------------------------- Servises ---------------------------------------*/


/** @brief Moves the king
 *
 * This function moves the king with selected speed
 * @param delay_1 first delay in ns
 * @param delay_2 second delay in ns
 */
void move_king(uint32_t delay_1, uint32_t delay_2);

/** @brief Moves the water
 *
 * This function moves the water with selected speed
 * @param delay_1 first delay in ns
 * @param delay_2 second delay in ns
 */
void move_water(uint32_t delay_1, uint32_t delay_2);

/** @brief Moves the pawn
 *
 * This function moves the pawn with selected speed
 * @param delay_1 first delay in ns
 * @param delay_2 second delay in ns
 */
void move_pawn(uint32_t delay_1, uint32_t delay_2);

/** @brief Moves the X axys
 *
 * This function moves the cariiage X axys with selected speed
 * @param delay_1 first delay in ns
 * @param delay_2 second delay in ns
 */
void move_x(uint32_t delay_1, uint32_t delay_2);

/** @brief Moves the Y axys
 *
 * This function moves the cariiage Y axys with selected speed
 * @param delay_1 first delay in ns
 * @param delay_2 second delay in ns
 */
void move_y(uint32_t delay_1, uint32_t delay_2);

/** @brief Sets the direction of the king.
 *
 * This function sets the direction of the king.
 * @param dir Direction of the king (0 = left, 1 = right)
 */
void set_king_dir(_Bool dir);

/** @brief Sets the direction of the water.
 *
 * This function sets the direction of the water.
 * @param dir Direction of the water (0 = up, 1 = down)
 */
void set_water_dir(_Bool dir);

/** @brief Sets the direction of the pawn.
 *
 * This function sets the direction of the pawn.
 * @param dir Direction of the pawn (0 = CCW, 1 = CW)
 */
void set_pawn_dir(_Bool dir);

/** @brief Sets the direction of the x axys.
 *
 * This function sets the direction of the carriage.
 * @param dir Direction of the carrige (0 = left 2 st, 1 = right 1 st)
 */
void set_x_dir(_Bool dir);

/** @brief Sets the direction of the Y axys.
 *
 * This function sets the direction of the carriage.
 * @param dir Direction of the carrige (0 = down 2 st, 1 = up 1 st)
 */
void set_y_dir(_Bool dir);

/** @brief Resets the STM32.
 *
 * This function resets the STM32.
 * @return ECOK
 */
enum ErrorCode resetSTM(void);

/** @brief Reads the state of a GPIO pin with debouncing.
 *
 * This function reads the state of a GPIO pin with debouncing.
 * @param GPIOx GPIO port
 * @param GPIO_Pin GPIO pin
 * @return Pin state
 */
GPIO_PinState HAL_GPIO_ReadPinDebounced(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


/** @brief Reads the state of kings LEFT stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_king_left_stoper(void);

/** @brief Reads the state of kings LEFT stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_king_left_stoper_Db(void);


/** @brief Reads the state of kings RIGHT stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_king_right_stoper(void);

/** @brief Reads the state of kings RIGHT stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_king_right_stoper_Db(void);

/** @brief Reads the state of waters UP stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_water_up_stoper(void);

/** @brief Reads the state of waters UP stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_water_up_stoper_Db(void);

/** @brief Reads the state of waters DOWN stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_water_down_stoper(void);

/** @brief Reads the state of waters DOWN stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_water_down_stoper_Db(void);

/** @brief Reads the state of pawns stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_pawn_stoper(void);

/** @brief Reads the state of pawns stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_pawn_stoper_Db(void);

/** @brief Reads the state of x axys left stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_x_left_stoper(void);

/** @brief Reads the state of x axys left stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_x_left_stoper_Db(void);

/** @brief Reads the state of x axys right stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_x_right_stoper(void);

/** @brief Reads the state of x axys right stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_x_right_stoper_Db(void);

/** @brief Reads the state of y axys up stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_y_up_stoper(void);

/** @brief Reads the state of y axys up stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_y_up_stoper_Db(void);

/** @brief Reads the state of y axys down stopper.
 *
 * This function reads without debouncing.
 * @return Pin state
 */
GPIO_PinState if_y_down_stoper(void);

/** @brief Reads the state of y axys down stopper.
 *
 * This function reads with debouncing.
 * @return Pin state
 */
GPIO_PinState if_y_down_stoper_Db(void);

/** @brief Check stopers
 *
 * This function check if both stopers is toggled
 */
enum ErrorCode check_stops(void);

#endif  //_SERVICES_H

