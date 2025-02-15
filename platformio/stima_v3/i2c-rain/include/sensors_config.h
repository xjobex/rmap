/**@file sensors_config.h */

/*********************************************************************
Copyright (C) 2017  Marco Baldinetti <m.baldinetti@digiteco.it>
authors:
Paolo Patruno <p.patruno@iperbole.bologna.it>
Marco Baldinetti <m.baldinetti@digiteco.it>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#ifndef SENSOR_CONFIG_H
#define SENSOR_CONFIG_H


/*!
\def SENSOR_MAX
\brief Max number of sensor.
*/
#define SENSORS_MAX      (1)

/*!
\def SENSOR_UNIQUE_MAX
\brief Max number of unique sensor.
unique sensors are sensors that can ghave more driver but only one i2c address and only one setup and prepare
*/
#define SENSORS_UNIQUE_MAX      (1)

/*!
\def USE_JSON
\brief Enable if you want use json library for json response (getJson function in SensorDriver).
*/
#define USE_JSON                    (true)

/*!
\def USE_SENSOR_ADT
\brief Enable if you want use ADT7420 sensor.
*/
#define USE_SENSOR_ADT              (false)

/*!
\def USE_SENSOR_HIH
\brief Enable if you want use HIH6100 sensor.
*/
#define USE_SENSOR_HIH              (false)

/*!
\def USE_SENSOR_HYT
\brief Enable if you want use HYT271 or HYT221 sensor.
*/
#define USE_SENSOR_HYT              (false)

/*!
\def USE_SENSOR_DEP
\brief Enable if you want use DigitEco Power sensor.
*/
#define USE_SENSOR_DEP              (false)

/*!
\def USE_SENSOR_OA2
\brief Enable if you want use OPC PM1, PM2.5, PM10 continuous average value.
*/
#define USE_SENSOR_OA2              (false)
#define USE_SENSOR_OA3              (false)

/*!
\def USE_SENSOR_OB2
\brief Enable if you want use OPC PM1, PM2.5, PM10 continuous standard deviation value.
*/
#define USE_SENSOR_OB2              (false)
#define USE_SENSOR_OB3              (false)

/*!
\def USE_SENSOR_OC2
\brief Enable if you want use OPC BINS continuous average value.
*/
#define USE_SENSOR_OC2              (false)
#define USE_SENSOR_OC3              (false)

/*!
\def USE_SENSOR_OD2
\brief Enable if you want use OPC BINS continuous standard deviation value.
*/
#define USE_SENSOR_OD2              (false)
#define USE_SENSOR_OD3              (false)

/*!
\def USE_SENSOR_OD2
\brief Enable if you want use OPC BINS continuous standard deviation value.
*/
#define USE_SENSOR_OE3              (false)

/*!
\def USE_SENSOR_LWT
\brief Enable if you want use leaf wetness time continuous value.
*/
#define USE_SENSOR_LWT              (false)

/*!
\def USE_SENSOR_HI7
\brief Enable if you want use SI7021 sensor.
*/
#define USE_SENSOR_HI7              (false)

/*!
\def USE_SENSOR_BMP
\brief Enable if you want use Bmp085 sensor.
*/
#define USE_SENSOR_BMP              (false)

/*!
\def USE_SENSOR_DW1
\brief Enable if you want use DW1 sensor.
*/
#define USE_SENSOR_DW1              (false)

/*!
\def USE_SENSOR_TBS
\brief Enable if you want use Tipping bucket rain gauge sensor.
*/
#define USE_SENSOR_TBS              (false)

/*!
\def USE_SENSOR_TBR
\brief Enable if you want use Tipping bucket rain gauge sensor.
*/
#define USE_SENSOR_TBR              (false)

/*!
\def USE_SENSOR_STH
\brief Enable if you want use Temperature and humidity oneshot sensor.
*/
#define USE_SENSOR_STH              (false)

/*!
\def USE_SENSOR_ITH
\brief Enable if you want use Temperature and humidity continuous istantaneous sensor.
*/
#define USE_SENSOR_ITH              (false)

/*!
\def USE_SENSOR_NTH
\brief Enable if you want use Temperature and humidity continuous minium sensor.
*/
#define USE_SENSOR_NTH              (false)

/*!
\def USE_SENSOR_MTH
\brief Enable if you want use Temperature and humidity continuous average sensor.
*/
#define USE_SENSOR_MTH              (false)

/*!
\def USE_SENSOR_XTH
\brief Enable if you want use Temperature and humidity continuous maximum sensor.
*/
#define USE_SENSOR_XTH              (false)

/*!
\def USE_SENSOR_SSD
\brief Enable if you want use SSD011 oneshot sensor.
*/
#define USE_SENSOR_SSD              (false)

/*!
\def USE_SENSOR_ISD
\brief Enable if you want use SSD011 report istantaneous sensor.
*/
#define USE_SENSOR_ISD              (false)

/*!
\def USE_SENSOR_NSD
\brief Enable if you want use SSD011 report minium sensor.
*/
#define USE_SENSOR_NSD              (false)

/*!
\def USE_SENSOR_MSD
\brief Enable if you want use SSD011 report average sensor.
*/
#define USE_SENSOR_MSD              (false)

/*!
\def USE_SENSOR_XSD
\brief Enable if you want use SSD011 report maximum sensor.
*/
#define USE_SENSOR_XSD              (false)

/*!
\def USE_SENSOR_SMI
\brief Enable if you want use MICS4514 oneshot sensor.
*/
#define USE_SENSOR_SMI              (false)

/*!
\def USE_SENSOR_IMI
\brief Enable if you want use MICS4514 report istantaneous sensor.
*/
#define USE_SENSOR_IMI              (false)

/*!
\def USE_SENSOR_NMI
\brief Enable if you want use MICS4514 report minium sensor.
*/
#define USE_SENSOR_NMI              (false)

/*!
\def USE_SENSOR_MMI
\brief Enable if you want use MICS4514 report average sensor.
*/
#define USE_SENSOR_MMI              (false)

/*!
\def USE_SENSOR_GWS
\brief Enable if you want use Gill Windsonic sensor.
*/
#define USE_SENSOR_GWS              (false)

/*!
\def USE_SENSOR_XMI
\brief Enable if you want use MICS4514 report maximum sensor.
*/
#define USE_SENSOR_XMI              (false)

/*!
\def USE_SENSOR_RF24
\brief Enable if you want use Radio RF24 sensor.
*/
#define USE_SENSOR_RF24             (false)

/*!
\def VALUES_TO_READ_FROM_SENSOR_COUNT
Maximum number of values to be read by the sensors.
*/
#define VALUES_TO_READ_FROM_SENSOR_COUNT      (3)
#define JSONS_TO_READ_FROM_SENSOR_COUNT       (3)

#endif
