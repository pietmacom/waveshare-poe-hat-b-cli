#!/bin/sh -e

_fanState="off"
_fanOnTemperature="40000"
_fanOffTemperature="35000"

while true; do
    _temperature="$(cat /sys/class/thermal/thermal_zone0/temp)"

    _temperatureViewAwk="BEGIN { printf \"%.2f C\", (${_temperature}/1000) }"
    _temperatureView=$(awk "${_temperatureViewAwk}";)

    if [[ "${_temperature}" > "${_fanOnTemperature}" ]]; then
	_fanState="on"
    elif [[ "${_temperature}" < "${_fanOffTemperature}" ]]; then
	_fanState="off"
    fi

    ./waveshare-poe-hat-b-cli fan ${_fanState}
    ./waveshare-poe-hat-b-cli oled "T: ${_temperatureView}" "F: ${_fanState}"
    sleep 3
done
