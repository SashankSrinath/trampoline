# PV Emulation with a programmable Power Supply

## Principle

The real PV+MPPT has:
 * **PV pannel**: gives $(V_{pv},I_{pv})$, depending on the load, sun irradiance, temperature, …
 * **MPPT**: from the solar pannel, find the tuple $I_{mppt}$,$V_{mppt}$ that gives the maximum power
 * **regulator**: gives a stabilized output voltage $V_{stab}$, and a maximum output current $I_max$, so that $V_{stab} \times I_{max} = e \times V_{mppt} \times I_{mppt}$, where $e$ is the regulator efficiency.

The emulator has:
 * the typical power/voltage curves for a pannel for different sun  irradiance (and temperatures, …)
 * Offline, we compute the maximum power $P_{max}$ that can be extracted for a given configuration (irrandiance/temperature).
 * at runtime, we simply configure the power supply with:
   * $V_{stab}$ (output voltage of the regulator)
   * $I_{max} = e \times \frac{P_{max}}{V_{stab}}$ the max current
 * when the parameters are updated, $P_{max}$ is also updated.

