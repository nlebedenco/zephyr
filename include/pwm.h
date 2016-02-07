/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @brief Public PWM Driver APIs
 */

#ifndef __PWM_H__
#define __PWM_H__

/**
 * @brief PWM Interface
 * @defgroup pwm_interface PWM Interface
 * @ingroup io_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define PWM_ACCESS_BY_PIN	0
#define PWM_ACCESS_ALL		1

#include <stdint.h>
#include <stddef.h>
#include <device.h>

typedef int (*pwm_config_t)(struct device *dev, int access_op,
			    uint32_t pwm, int flags);
typedef int (*pwm_set_values_t)(struct device *dev, int access_op,
				uint32_t pwm, uint32_t on, uint32_t off);
typedef int (*pwm_set_duty_cycle_t)(struct device *dev, int access_op,
				    uint32_t pwm, uint8_t duty);
typedef int (*pwm_suspend_dev_t)(struct device *dev);
typedef int (*pwm_resume_dev_t)(struct device *dev);

/** @brief PWM driver API definition. */
struct pwm_driver_api {
	pwm_config_t config;
	pwm_set_values_t set_values;
	pwm_set_duty_cycle_t set_duty_cycle;
	pwm_suspend_dev_t suspend;
	pwm_resume_dev_t resume;
};

/**
 * @brief Configure a single PWM output.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param pwm PWM output.
 * @param flags PWM configuration flags.
 *
 * @retval DEV_OK If successful,
 * @retval failed Otherwise.
 */
static inline int pwm_pin_configure(struct device *dev, uint8_t pwm,
				    int flags)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->config(dev, PWM_ACCESS_BY_PIN, pwm, flags);
}

/**
 * @brief Set the ON/OFF values for a single PWM output.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param pwm PWM output.
 * @param on ON value set to the PWM.
 * @param off OFF value set to the PWM.
 *
 * @retval DEV_OK If successful.
 * @retval failed Otherwise.
 */
static inline int pwm_pin_set_values(struct device *dev, uint32_t pwm,
				     uint32_t on, uint32_t off)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->set_values(dev, PWM_ACCESS_BY_PIN, pwm, on, off);
}

/**
 * @brief Set the duty cycle of a single PWM output.
 *
 * This routine overrides any ON/OFF values set before.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param pwm PWM output.
 * @param duty Duty cycle to set to the PWM in %, for example,
 *        50 sets to 50%.
 *
 * @retval DEV_OK If successful.
 * @retval failed Otherwise.
 */
static inline int pwm_pin_set_duty_cycle(struct device *dev, uint32_t pwm,
					 uint8_t duty)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->set_duty_cycle(dev, PWM_ACCESS_BY_PIN, pwm, duty);
}

/**
 * @brief Configure all the PWM outputs.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param flags PWM configuration flags.
 *
 * @retval DEV_OK If successful.
 * @retval failed Otherwise.
 */
static inline int pwm_all_configure(struct device *dev, int flags)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->config(dev, PWM_ACCESS_ALL, 0, flags);
}

/**
 * @brief Set the ON/OFF values for all PWM outputs.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param on ON value set to the PWM.
 * @param off OFF value set to the PWM.
 *
 * @retval DEV_OK If successful.
 * @retval failed Otherwise.
 */
static inline int pwm_all_set_values(struct device *dev,
				     uint32_t on, uint32_t off)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->set_values(dev, PWM_ACCESS_ALL, 0, on, off);
}

/**
 * @brief Set the duty cycle of all PWM outputs.
 *
 * This overrides any ON/OFF values being set before.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param duty Duty cycle to set to the PWM in %, for example,
 *        50 sets to 50%.
 *
 * @retval DEV_OK If successful.
 * @retval failed Otherwise.
 */
static inline int pwm_all_set_duty_cycle(struct device *dev, uint8_t duty)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->set_duty_cycle(dev, PWM_ACCESS_ALL, 0, duty);
}

/**
 * @brief Save the state of the device and makes it go to the low power
 * state.
 *
 * @param dev Pointer to the device structure for the driver instance.
 *
 * @retval DEV_OK If successful.
 * @retval failed Otherwise.
 */
static inline int pwm_suspend(struct device *dev)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->suspend(dev);
}

/**
 * @brief Restore state stored during suspend and resumes operation.
 *
 * @param dev Pointer to the device structure for the driver instance.
 *
 * @retval DEV_OK If successful.
 * @retval failed Otherwise.
 */
static inline int pwm_resume(struct device *dev)
{
	struct pwm_driver_api *api;

	api = (struct pwm_driver_api *)dev->driver_api;
	return api->resume(dev);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __PWM_H__ */
