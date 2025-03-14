#include <pawnio.inc>

const IA32_THERM_STATUS = 0x19C;
const MSR_TEMPERATURE_TARGET = 0x1A2;
const IA32_PACKAGE_THERM_STATUS = 0x1B1;

// bits 16~22 contain the current reading as a negative offset from TCC activation temperature (returned by MSR_TEMPERATURE_TARGET)
forward ioctl_get_therm_status(in[], in_size, out[], out_size);
public ioctl_get_therm_status(in[], in_size, out[], out_size) {
    if (out_size < 1)
        return STATUS_BUFFER_TOO_SMALL;

    new value;
    msr_read(IA32_THERM_STATUS, value);
    out[0] = value;

    return STATUS_SUCCESS;
}

// bits 16~22 contain the current reading as a negative offset from TCC activation temperature (returned by MSR_TEMPERATURE_TARGET)
forward ioctl_get_package_therm_status(in[], in_size, out[], out_size);
public ioctl_get_package_therm_status(in[], in_size, out[], out_size) {
    if (out_size < 1)
        return STATUS_BUFFER_TOO_SMALL;

    new value;
    msr_read(IA32_PACKAGE_THERM_STATUS, value);
    out[0] = value;

    return STATUS_SUCCESS;
}

// bits 16~23 contain the default temperature target (Package on most CPUs, Thread on some CPUs. Probably only for the writable bits though?)
forward ioctl_get_temperature_target(in[], in_size, out[], out_size);
public ioctl_get_temperature_target(in[], in_size, out[], out_size) {
    if (out_size < 1)
        return STATUS_BUFFER_TOO_SMALL;

    new value;
    msr_read(MSR_TEMPERATURE_TARGET, value);
    out[0] = value;

    return STATUS_SUCCESS;
}

main() {
    if (get_arch() != ARCH_X64)
        return STATUS_NOT_SUPPORTED;

    new vendor[4];
    cpuid(0, 0, vendor);
    if (!is_intel(vendor))
        return STATUS_NOT_SUPPORTED;

    new thermalinfo[4];
    cpuid(6, 0, thermalinfo);

    if (!(thermalinfo[0] & 1))
        return STATUS_NOT_SUPPORTED;

    return STATUS_SUCCESS;
}
