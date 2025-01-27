# Release notes

## Release 0.8.11 "Accomplishment" - Towards full equation library

This release contains a number of fixes and features intended for use in the
equation library being contributed by Jean Wilson

### Features

* Accept library items for functionc calls. For example, the expression
  `'ⓁSiDensity(273_K)'` is now accepted. This function is usd in semi-conductor
  equations in the library.
* The `Root` command now attempts symbolic solving using the `Isol` command.
  This can lead to exact solutions for common equations.
* The `SigDig` command is a DB48x extension that returns the number of
  significant digits in a number, i.e. the number of non-zero digits.
* The `xpon` and `mant` now apply to unit objects
* Functions now accept assignments as input, e.g. `x=9` `sqrt` gives `3.0`
* The equation referenced to by the `Equation` variable can now be identified
  using a name.
* The `NxEq` command now works with quoted equations

### Bug fixes

* The `ln(1E-100)` expression no longer gives a `Argument outside domain`
  error. The error was caused by rouding during argument reduction.
* Comparison between a value and a unit object now work correclty
* Arithmetic now correctly deals with dimensionless unit objects, for example in
  expression `'1-1000_mm/m'`, and improves the evaluation of unit expressions
  when adding or subtracting unit objects.
* Names containing programs or functions are now evaluated as part of algebraic
  evaluation
* The solver now correctly processes equations wrapped in an expression.
* `Convert` now correclty evaluates its arguments when necessary
* Assignment objects no longer cause a crash on error. For example, `x='ln(0)'`
  no longer crashes.

### Improvements

* Improve solver heuristic when slope is small. This allows the solver to find a
  solution for an equation like `'tan(x)=224'` in degrees mode.
* Add more recorder entries in the solver describing what is being solved.
* Move recorder entries for tests to `tests` data logger.
* Tests use a larger text rendering limit
* Tests now purge the directory between examples. This prevents stray variables
  from influencing later tests.
* The handling of long UTF-8 sequences in tests was improved, which allows tests
  involving a lot of text (e.g. examples) to run faster.


## Release 0.8.10 "Fire Dove" - Input and Prompt, Android preparation

The focus of this release is support for user input in programs, with
the addition of the `Input` and `Prompt` commands. Internally, a lot
of groundwork was performed towards Android builds.

### New features

* Add `Prompt` command, which programs can use to let users manipulate
  the stack or do other operations before resuming execution.

* In order to facilitate the use of `Prompt`, added the `Run` command,
  which resumes execution of halted programs and otherwise evaluates
  the first item on the stack. The key at the left of the _+_ key,
  which is labeled _R/S_ on the DM-42 calculators, is now bound to the
  `Run` command instead of `Evaluate`. Therefore, after a `Prompt`,
  you can resume execution with a single key.

* Add `Input` command, which programs can use to let users enter data.
  The DB48x version makes it easier to enter and validate numerical
  data or other non-text objects, with input validators for numbers,
  integer values, arithmetic objects or expressions. It is also
  possible to use custom code to validate user input.

* Additional `Compile` variants were created to help with this user
  input validation, checking if the input is a number, an integer, a
  positive integer, a real number, a single object, a single algebraic
  object or an expression.

### Bug fixes

* Fixed problem with the computation of the length of the integer
  value being parsed if it was parsed from a text value at the end of
  the temporaries.

* Emit an error from `Step` and variants if no program is being
  debugged. The effect was that the next program being run would halt
  after the first step.

* Avoid persisting beep in the simulator when two beeps were emitted
  rapidly in successioon.

* Reload the user-selected keymap file after loading the state file.

### Improvements

* Change capitalization of `DTag` as a shortcut for `DeleteTag`.

* Various code improvements making it easier to compile for Android.
  A side effect is that the simulator can now safely be started from
  any current directory.

* Improve rescaling of the window in the simulator to keep the
  keyboard and screen larger and easier to read.

* Improve the detection of the default simulator size for Hi-DPI
  screens.

* Add documentation about matrix multiplication performance

* Make the default memory size more consistent with the simulated
  device.



## Release 0.8.9 "Advent" - Mostly bug fixes

This is a relatively minor release, with mostly bug fixes, but also a
new, explicit syntax for hardware-accelerated floating-point.


### New features

* Hardware-accelerated IEEE-754 binary floating-point values are now
  identified with a suffix, `D` for `double` (64-bit), `F` for
  `float` (32-bit). For example, `1.23` is a variable-precision
  decimal value, `1.23D` is a 64-bit binary floating-point value, and
  `1.23F` is a 32-bit binary floating-point value. This ensures that
  the `HardwareFloatingPoint` setting does not change the way a
  program is compiled or presented, only its computations.
* plot: Draw a bar on the horizontal axis for errors.
  This makes it easier to identify where the function is not defined.
* probabilities: Extend `COMB` and `PERM` to real arguments
  For real argument, the Gamma function extension of the factorial is
  used with the usual expressions to compute combinations and
  permutations. One user remarked that some half-integer combinations
  of arguments, for example, directly give some common Taylor series
  factors with a single expression.
* decimal: Add decimal to integer conversion (`R→I`)
* simulator: Add `-N` option to disable sound. This is notably useful
  on Linux where some hardware platforms takes tens of seconds to
  fail, slowing down error messages.
* simulator: Recognize settings on the command line. For example, you
  can enable the _silent beep_ feature (flashing screen on error) by
  passing the `SilentBeepOn=true` parameter on the command-line.
* parser: Add `PREC` alias for `Precision`.


### Bug fixes

* random: Fix bias in integer version of `Random`. Using `1 10 Random`
  would generate values `1` and `2` at half the frequency of other
  values.
* help: Do not process links that are not visible. This could cause
  links that had scrolled past the top of the screen to be incorrectly
  selected when pressing the _ENTER_ key, even if there was an RPL
  code example visible on the screen.
* simplifications: Do not simplify infinities. Earlier versions would
  incorrectly apply a rule like `X-X=0` to the case where `X` was an
  infinity, giving incorrect results. This could manifest for example
  in `Comb` with decimal input returning `1` for large values (as a
  result of dividing `∞` by `∞`) and `Det` returning `0` (as a
  result of subtracting `∞` from `∞`).
* expression: Fix rendering of `derivative`, `primitive` and `where`
  in HP compatibility mode. This could cause programs to become
  unparseable, e.g. with `∂X(X+1)` turning into `DERIVATIVEX(X+1)`.
* expression: Do not render arity-2 commands as infix. For example,
  `CONVERT(X;1_m/s)` no longer renders as `X CONVERT 1_m/s`.
* simulator: Improve extension checks on case-independent filesystems.
  On such systems, files `foo.48s` and `FOO.48S` are identical. The
  simulator could incorrectly add a second extension if the case did
  not match.
* arcsin: Fix the incorrect computation of `arcsin(1)`. More
  generally, improve the way exact angles are generated by functions
  that require them. This allows such functions to now return
  non-rounded results when using angle modes such as `degrees`.
  Previously, a computation involving the value of the `π` constant
  would cause some rounding even if an exact result was possible.
* Fix a rare bug in the user interface which could lead to memory
  corruption if a garbage collection happened at the wrong time.
* Accelerated arithmetic evaluation is now correctly disabled when the
  `HardwareFloatingPoint` setting changes.
* Fix silent errors when `NumericalResults` is on and computations
  involve non-normal results (e.g. infinities).
* Convert infinities correctly from hardware floating-point to
  decimal.

### Improvements

* simulator: Return relative paths when selecting files when possible.
  For example, when selecting the name of a keyboard layout, a file is
  written on disk that used to contain the absolute path of the
  layout file being used. As a result, moving the simulator directory
  elsewhere would make the file unreadable.
* files: Automate tracking of open files. A mechanism was implemented
  in earlier releases to avoid opening two files at the same time,
  because that is a limitation of the DMCP implementation on
  SwissMicros calculators. That mechanism required manual maintenance
  by developers, and was the source of many bugs. A new mechanism
  replaces it that transparently manages scenarios where multiple
  files are open simultaneously. This should quash annoying bugs, such
  as one where the simulator would write state files with incorrect
  spelling for constants or library items.
* doc: Remove the `docol.md` section of the help. This file was
  inherited from newRPL documentation, and incorrectly documented
  existing DB48x functions, or mentioned functions that do not exist
  on DB48x.
* grob: Accept BMP files with zero colours. Some contributors have
  submitted files generated by Windows tools that describe the BMP
  file as a bitmap with 0 colours instead of 2. These files were not
  loading in the helpfile. They are now read and displayed correctly.
* Hardware-accelerated floating-point arithmetic now also benefits
  from the accelerated dynamic dispatch.

## Release 0.8.8 "Voice" - Power usage reduction

This release focuses on reducing power usage and improving reactivity,
notably while running on battery.

### Features

* Cache rendered graphics and text on the stack to reduce the time
spent redrawing the stack.

* Limit the size of objects being rendered on the stack. Objects that
  are too large will simply render as something like `Large bignum
  (399 bytes)` on the stack. This is configured by two new settings,
  `TextRenderingSizeLimit` and `GraphRenderingSizeLimit`.

* Limit the size spent rendering graphical objects. There are four
  settings controlling the maximum time spent rendering objects
  graphically.  `ResultGraphingSizeLimits` controls the display for
  the first level on the stack, `StackGraphingSizeLimit` controls the
  display for the other levels on the stack, `ShowTimeLimit` controls
  the display for the `Show` command, and `GraphingTimeLimit` controls
  other graphical rendering.

* Blink the battery icon when in a low-battery situation.

* Add configurable `MinimumBatteryVoltage` to adjust the threshold for
  low-battery detection and automatic power-off.

* Power-related commands: The `BatteryVoltage` and `PowerVoltage` read
  the battery and power voltage respectively. The `USBPowered`
  commands detects if the calculator is running on USB power. The
  `LowBattery` command detects if the calculator is running low on
  battery.

* Detect and reject Unicode characters that look like mathematical
  characters, and are produced by auto-correction on Windows, notably
  the`-` and `*` signs that look like `-` and `*`. This is notably
  useful when copy-pasting in the simulator on Windows.

### Bug fixes

* Fix `NDupN` again. While the previous release fixed what `NDupN`
  does, it did not fix the detection of the number of arguments,
  meaning that `NDupN` would incorrectly complain about missing
  arguments if the stack was not deep enough.

* Fix the precedence of unary `-` when in front of a parenthesized
  expression.  For example, `-(X)^2` now parses correctly.

* Disable keyboard repeat timer when no key is pressed. It was
  possible to trigger a condition where the keyboard repeat timer
  would trigger continuously if two keys had been pressed in rapid
  succession, keeping the CPU in a busy loop and depleting the battery
  unnecessarily rapidly until another key was pressed. This could also
  trigger incorrect long-press detections, e.g. the shift key
  triggering alpha mode instead of a simple shift.

* Disable all timers when switching the calculator off. In some
  situations, the display refresh timer could still remain active
  after the calcualtor had been switched off.

* `RclΣ` now returns the statistics data even when the `ΣData`
  variable contains the name of a variable or file.

* The `Off` command can now be used while editing and no longer causes
  immediate command-line evaluation.

* Return to the first page of the catalog menus when updating it, to
  avoid scenarios where the catalog appeared empty

* Return to the first page of the cartalog menu when changing
  directories, to avoid showing an empty variables menu in a non-empty
  directory.

* Do not leave garbage on the stack after failed array arithmetic.

* Avoid occasional test crashes due to concurrent pixmap updates in
  the simulator.

* Avoid occasional spurious error on `Primitive` test due to long
  execution time.

* Switch to `kg` as the base unit for `UBASE` instead of `g`,
  following the SI standard.

### Improvements

* Reduce animations more drastically while on battery power.
  Notably, the cursor does not blink, and menu animations are entirely
  disabled.

* Rework the animation and screen refresh system to make it easier to
  maintain and more power-efficient while on battery.

* Refresh the display using hardware-accelerated background refresh
  routines provided by the DMCP platform. This can be disabled using
  the `SoftwareDisplayRefresh` flag.

* Redraw the battery immediately on power change, i.e. plugging or
  unplugging the USB cable.

* Updated built-in constants with latets CODATA values
  (contributed by Jean Wilson)


## Release 0.8.7 "Signs" - Performance optimizations

This release focuses on performance improvements and bug fixes for
issues reported by users and contributors.

### Features

* Long array operations such as matrix multiplications can now be
  interrupted with the EXIT key.

* Eliminate local names from `LNAME` output. For example, if you
  perform a sum with a variable named `i` as an index, no longer
  report `i` as being a name used by the expression..

* Implement `HEAD` and `TAIL` for text objects.

* Allow constant definitions to contain expressions, which will be
  fully evaluated when using the `→Num`. This makes it possible to now
  define constants using other constants, in the spirit of the more
  recent CODATA recommandations.

* Library management commands `Attach`, `Detach` and `Libs` are now
  implemented. These commands make it possible to reload a library
  entry after changing its definition on disk. While they take
  arguments that are similar to what HP calculators do, they are not
  interpreting them in the same way due to hardware differences
  between SwissMicros and HP calculators.


### Bug fixes

* Fix hard crash when running some RPL programs using conditional
  loops, local variables and/or deep recursion. The crash was caused
  by a non-robust check of whether the call stack needed to grow or
  shrink, which was replaced with a much more robust check.

* Fixed the precedence of the unary `-` operator, so that `-X^2` now
  parses correctly (it used to be interpretd as `(-X)^2`)

* Fix a crash where an error during an array operation could cause a
  null pointer to be pushed on the stack.

* The test suite now correctly reports error detected while
  checking the examples in the online help.

* The multi-solver no longer considers the index variable in a sum or
  product as a variable to solve for. This avoids spurious errors
  claiming that a solution cannot be found. The same also applies
  other functions that take a variable name as an argument, such as
  `Root`, `Integrate` or `Isolate`.

* Fix a crash when comparing unit objects that cannot be converted
  from one to the other, e.g. comparing `1_m` and `1_h`.

* Fix the order of commands in the build instructions for Windows.

* Fix the `NDupN` command to duplicate an object N times. In earlier
  releases, it was incorrectly duplicating N objects and leaving  N on
  the stack.

* Accept addition and subtraction between a number and a unit object
  where the unit can be reduced to a number, so that `'1+1_km/m'` is
  now a valid expression. A few additional entries in the equation
  library now work thanks to that fix.

* Avoid a rare crash where the error command would be corrupted when
  cleaning temporaries.

### Improvements

* Performance optimizations for decimal arithmetic, using 25x25 matrix
  multiplication as a test scenario to optimize. The performance of
  such multiplication was improved by about one order of magnitude,
  and is now comparable to DM42 performance. This was achieved in
  particular by making more aggressive cleanup of temporaries, by
  reducing the need for garbage collection, by adding a fast-tracked
  path for arithmetic operations when the types are the same as for
  the last operation, and by deferring the construction of arrays
  until the value of all elements are computed.

* Add a few new sanity checks for the runtime when running on the
  simulator, notably to detect cases where the internal pointers are
  not in the expected order, and to more precisely report issues if
  integrity checks fail during garbage collection

* Add locking to the garbage collected pointers list when running on
  the simulator, in order to improve test stability. Testing on the
  simulator is the one case where multiple threads may concurently
  access the pointers list.

* Accelerate the tests that insert large amounts of text from source
  code, notably the equation parsing tests and the help examples
  checks. In addition, use a smarter method to insert RPL separators
  such as `[]` or `''`, taking advantage of the fact that they are
  usually entered in pairs. These two improvements reduce the total
  runtime of the entire test suite by a factor of more than 4.

* While testing the online help examples, only report the exact
  section title and not all the section titles that contain the same
  text.

* Systematically strip tags and assignment objects for all arithmetic
  operations.

* Add a version of the `debug_printf` that automatically selects where
  to draw on the screen, and automatically clear what follows the
  printed text using a gray pattern.

* Render the DB48x TrueType font to bitmap using a more recent version
  of the FreeType library. This causes minor glyph differences
  compared to earlier releases. The test suite was adjusted
  accordingly.

* Remove some of the leftover references to newRPL commands that will
  not be implemented or make no sense for DB48x. This work is not
  finished yet. The mechanism to remember which command caused a
  particular error was also made somewhat more efficient.

* Consolidate the two distinct documentations of the `Root` command.


## Release 0.8.6 "Daniel" - Bug fixes and optimizations

This release is mostly intended to fix a number of issues reported by
users or discovered during testing.

### Features

* Fancy digits are now accepted for decimal and based numbers.
  This means that `1.⁳³²` is now a valid input to `Str→`, ensuring
  that we can parse the output of `→Str` if it uses fancy characters,
  or that copy-paste works from the stack to the editor.
* Accept array arguments for `min` and `max`, applied element-wise in
  the same way as addition for example.
* Add `CompatibleBasedNumbers` setting to render `16#AB` as `#ABh`
  like HP calculators.
* Improve protection against mismatched QSPI and PGM. Only binaries
  issued from the same build are now accepted. This is mostly of
  interest to developers, although releases that are very close to one
  another, like v0.8.4 and v0.8.5 were, can require this protection.
* On DM32, numbers with an explicit numerical base keep that base if
  it's 16, 10, 8 or 2. For example, `10#200` and `#200₁₀` will display in
  base 10 irrespective of the `Base` setting, just like `#200d`.
* Add `ϵ` character (Greek Lunate epsilon), which appears in some
  equations.
* Add text alignment options to `DrawText`, making it possible to
  align text horizontally or vertically. See examples at end of the
  `Texts` program in `Demo.48s`
* Add `UnitsSIPrefixCycle` command to set the variable with the same
  name to customize SI prefixes cycling for units on the command-line.
  After `"KMG" UnitsSIPrefixCycle`, typing the `Cycle` key (__×10ⁿ_ or
  _EEX_) with `1_B` will cycle through `1_KB`, `1_MB`, `1_GB` and back
  to `1_B`.
* Accept `u` as an alternative SI prefix for "micro-", e.g. `1_us`.
  This is intended to allow entering of the "micro" prefix using
  transient alpha mode.
* Add help lookup for solver variables. When in the `SolverMenu`,
  holding the function key for a vairable brings up the help for the
  corresponding variable in the equations library.
* Add `SiDensity` (`SIDENS` on HP) and `Fanning` functions to the
  library. These functions are used by some equations in the library.
* Add `invert` alias for 1/x operation (like `negate` for `neg`).


### Bug fixes

* Fix unit scale cycling for multi-character units
* Fix incorrect computation of output matrix size for non-square
  matrices. `[[1 2]][[3 4]] +` now works.
* Negation on based numbers and polynomials now works.
* Conversion of decimal values smaller than 1.0 to integer no longer
  crashes (this could only happen with the `RanM` command)
* Render `-` for first term of polynonials if negative
* On DM42, update the bases menu when cycling based numbers
* Fix parameter mixup for call to `program::run`. In theory, this
  could lead to programs not evaluating correctly if `NoLastArguments`
  setting was set, although another bug apparently made this very
  unlikely to be observed.
* Update index footer to point to `https://48calc.org` instead of
  obsolete `https://github.io` location.
* Updating a `for` loop variable from within the loop now behaves like
  on HP calculators, and can be used to control loop exit.
* Do not draw activity indicator in graphical mode. This was a
  regression introduced with `BusyIndicatorRefresh`.
* Mark `xroot` command as implemented in the `PowersMenu`
* Use consistent case for variable `x` in the equations library
* Do not error out comparing text values
* doc: Fix typo `latter` -> `letter`


### Improvements

* Add auto-cleaner optimizations for matrix and vector operations.
  This reduces the memory usage and frequency of garbage collections.
* Reduce `random` bias for integer input, e.g. `-10 10 random` no
  longer has a +0.5 bias on average.
* doc: Several updates and fixes to the documentation, notably with
  respect to the description of the current status, and instructions
  for Windows developers.
* Add `→Prg` alias for `→Program`
* Add the simulator minimum window size
* Add `rmdir` as an alias for `pgdir`. "This is Unix".
* Add `L` (uppercase) spelling for "liter" unit
* doc: Avoid overlapping aliases in `Rcl/` help text by adding some
  aditional text to the `Rcl*` help.
* doc: Add documentation for `SolverMenuSolve` and `SolverMenuRecall`
* doc: Fix documentation for `AssignKey`
* doc: Add documentation for comparisons
* doc: Remove duplicate `dup`
* doc: Update documentation about `add`
* doc: Refer to `CharactersMenu` and `Catalog` in alpha overview
* doc: Update keyboard sequences typography
* doc: Remove false claim that interactive stack is not implemented
* doc: Update implemented / unimplemented list


## Release 0.8.5 "Stone" - Emergency keyboard fixups

The major changes in 0.8.4 caused some damage to keyboard handling
code that require a few emergency fixes.

### Bug fixes

* Fix incorrect selection of lowercase characters

* Fix the location of `exp` and `log10` in `42style` and `true42`
  keymaps.

* Do not enter interactive stack if reaching leftmost position of the
  text editor.


## Release 0.8.4 "Commands" - Optimizations and equation fixups

This release focuses on improving the solver support for the equation
library, fixing various bugs found during development of that equation
library, and optimizing the garbage collector.

### Features

* ui: The keyboard layout is now configured by a a `config/[keymap].48k`
  file that describes which commands are assigned to which key by
  default. A new setup entry, `Load keymap`, lets you change the
  keyboard layout.

* ui: Add four predefined keyboard layouts:

  * `db48x.48k` is a key layout that is more logical and effective for DB48x
    [See thread](https://www.hpmuseum.org/forum/thread-20157-post-193647.html#pid193647)
  * `legacy.48k` is the layout used for earlier releases, which
    swaps the `exp` and `log10` keys relative to the DM42 in `42style.48k`.
  * `42style.48k` keeps key layout as close as possible to the DM42
  * `true42.48k` is identical to `42style.48k`, but the simulator shows an image
    of the DM42 keyboard.

* Add various commands such as `Edit` to directly perform editing
  operations in a programmatic way.

* units: Implement non-proportional unit conversions, notably
  temperature conversions like `°F` to `°C`. The underlying engine
  allows arbitrary conversions, including non-linear ones, which would
  be useful for example for the Dalton temperature scale. However,
  that capability is not presently used.

* units: Convert temperatures to `K` in multiplication and
  division. For example, when computing `ⒸR*T`, we need the
  temperature `T` to be in `K` even if given in Celsius or Farenheit
  initially.

* solver: Report underlying evaluation error. For example, if the
  expression being evaluated reports `Inconsistent units`, this is
  what the solver will return instead of `No solution?`.

* ui: Add configurable interval for busy cursor drawing,
  `BusyIndicatorRefresh`.  The default is now 50ms, which refreshes
  the busy cursor more frequently than before, and may be detrimental
  to battery life and performance. You can restore the previous
  behaviour by setting a higher value, e.g. 1000ms.

* performance: Automatic cleanup of temporaries to minimize the number
  of garbage collection occurences. When a complex operation such as
  `exp` is performed, there are a number of intermediate results that
  require storage, and were previously only cleaned up by the garbage
  collector. They are now automatically cleaned up before the function
  returns. The same optimization applies to intermediate graphics
  while rendering equations, notably on the stack. This delivers
  [significant performance improvements](#garbage-collector-performance)
  for long-running operations:
  the "[floating-point sum test](https://www.hpmuseum.org/forum/thread-9750.html)
  is now about 20% faster on SwissMicros calculators.

* commands: Add `GCStats` command to show garbage collector statistics.

* Allow `CustomMenu` to contain the name of a menu, or a program that
  builds the menu dynamically. An example is shown in the `RPL`
  directory of the Demo file.

* Allow `CustomMenu` to define "vertical" menus, i.e. menus where the
  items are stacked on top of one another.

### Bug fixes

* Fix functions taking real-like unit input. For example,
  `atan(1_cm/1_m)` now computes correctly.

* solver: Do not solve system of equations using existing values. The
  multiple equation solver would incorrectly consider existing values
  in variables to check if an equation could be used for solving. The
  heuristic now picks up the equation that requires the smallest
  number of unknown variables among the available equations.

* Parse `x!` as factorial of `x` and not as a `x!` symbol. The
  incorrect parsing was due to an ambiguity in the HP48 parser that
  was resolved in the HP50G. DB48X now behaves like the HP50G and does
  not allow `!` to appear at the end of a name.

* Do not enter the debugger if `DebugOnError` is set while evaluating
  an `iferr` statement. The assumption is that if you try to catch an
  error, you do not intend to debug the code being tested for an
  error. If this is not the desired behaviour, then an explicit
  `DebugOnError` should be inserted in the body of `iferr`.

* Various unit-related fixes in the equation library.

* Ensure that we don't execute auto-completed catalog commands
  twice. The recent change that added the auto-completed command to
  the command-line history also caused the command to be executed on
  the command-line before being evaluated again from the key.

* Avoid a rare crash when an equation was too big to be rendered
  graphically and a garbage collection cycle occured between graphic
  rendering and text rendering.

* Do not emit error message from `Vec→` for vectors containing
  units. The incorrect error was introduced by the logic detecting
  polar, cylindrical or spherical vectors.

* Fixed `atan2` special cases to always generate the correct
  angle. Cases where `atan2` would generate an exact result would
  usually result in the wrong angle unit scaling being applied.

* Fixed parsing of `tan⁻¹` in expressions.

* units: Skip the `=Cycle` section for unit definitions. This was
  causing incorrect unit conversion errors for users who had added
  common units in the `=Cycle` section of their `config/units.csv`
  file.

* The user-defined units menu no longer list all the built-in units
  after the user-defined ones.

* Add a missing `sqrt` in the `RelativisticKineticEnergy` sample code,
  and do not compute the kinetic energies for negative values.

* Alias `keys` is for `KeyMap`, not `Header`. Fix typo in identifiers
  table.

* Avoid a crash in `RandomMatrix` when hardware floating-point is
  enabled, due to an incorrect conversion to integer. As a side
  effect, fixed a couple of minor issues in the conversion to integer
  values from decimal or binary floating-point values.

* Fix bogus `Bad argument type` message for `V→` when the number of
  elements was not 2 or 3.

* Fix crash when dividing a matrix by a non-invertible matrix.

* Fix crash displaying non-normal hardware floating-point values.

* Fix crash in vector operations that cause errors, e.g. `[1][0] /`.

* Parse `ubase` algebraic expressions, e.g. `ubase(1_km)`, as well
  as other function-like commands such as `size`.

* Accept numerical values in `ubase` and leave them as is.

* Adjust the "next step" computation in the solver to minimize the
  complexity of conversions and remove unit ambiguity for temperatures.

* Rewrite the Heat Transfer equations to clarify temperature unit used
  in the computation. Specifically, avoid having a `ΔT` in a
  multiplication, where the value would be incorrectly converted to
  `K`.

* Fix a problem when a garbage collection while parsing a fraction
  could cause a large fraction of the subsequent program to be
  skipped. This normally led to anomalous `Inconsistent units`
  messages when this caused a unit such as `254/10_mm` for `in` to be
  incorrectly parsed as `254/10`.


### Enhancements

* Major update to the documentation of the equation library,
  contributed by Jean Wilson.
* equations: Replace `°F` with `°C` in equations
* tests: Add support for tests that are known to fail
* tests: Run equation tests with `11 DIG`
* tests: Add ability to take screen snapshots on failure
* units: Put temperatures before pressure in `Fluids` section
* help: Add image for B Field From Finite Wire
* Makefile: When using `make update`, do not keep the temporary `.png`
* Indicate where to get `tac` in the build documentation
* Fix README link to browser version
* Disable `DebugOnError` by default, since it confused new users
* Enhance the test suite so that it looks up the keys to use.
  This makes the test suite more readable, e.g. we have `ID_exp` in
  the test instead of `D` (the `D` key being where `exp` was on the
  original layout), and it makes the test suite layout-independent,
  paving the way for reuse on other hardware (e.g. HP50G).


## Release 0.8.3 "Blindness" - User mode and custom header

This release focuses on various user interface aspects.

### Features

* User mode, key assignment, `ASN`, `STOKEYS`, `RCLKEYS`, `DELKEYS`. Unlike HP
  calculators, key assignments are per directory, with inner directories
  inheriting the key assignments from the enclosing directories.
* Add `Header` command to customize the header. For example, you can now show
  the path in the header, or any relevant information. This customization can be
  done per-directory.
* Implement `Menu`, `TMenu` and `RclMenu` commands
* help: Automatically create links for references to RPL words.
  When we have `sin` in the Markdown file, the calculator will automatically
  insert a hyperlink to the corresponding entry. Note that this only applies to
  the calculator, not to the GitHub rendering of the Markdown files.
* Display object type in the `Info` box of the interactive stack.
* Fallback graphic rendering of objects to text when the usual heuristics did
  not allow the graphics to fit in the alloted pixel space. For example, a
  fraction that does not fit will now display using the textual form if that
  particular form can fit in the given box.

### Bug fixes

* Fix a bug that could cause the text editor cursor to move past the end of the
  editor when inserting text, possibly causing memory corruption.
* The `Show` command will now show all digits, and render fractions using
  multiple lines for the numerator and denominator so as to be able to show more
  digits in a readable way.
* When terminating a command using auto-completion in the `Catalog` feature, the
  command that was entered is now present in the command-line history.
* Arithmetic operations that combine text or lists and unit objects now behave
  correctly. For example, adding a unit to a list appends like any other object.
* directories: Move updir if evaluating an updir directory, instead of
  corrupting the directory stack.
* Clear transient object if entering the interactive stack, e.g. when exploring
  the interactive stack while in the `SolvingMenu` and solving an equation, and
  correctly update the transient object when switching menus.
* Render vectors as RPL code in the equation examples.
* Correctly redraw the text editor when using the interactive stack `Echo`
  feature with stack items spanning multiple lines
* Fix minor typos in the equations documentation.


### Improvements

* tests: Only evaluate after parsing RPL examples in the documentation when the
  stack is not empty
* The `Wait` command now returns a key code in the same style as HP calculators,
  i.e. with row, column and plane. Also, like HP calculators, it processes shift
  keys and returns a plane, instead of returning the keycode of the shift key.
* Capitalize `Path`, `CrDir`, `Home`, `UpDir` so that their rendering in
  compatibility mode with the `Cmd` setting looks better.
* Add `DB48X_SPEEDUP` environment variable support in the simulator.
* documentation: Update Authors section


## Release 0.8.2 "Honor Seats" - Equation Library Examples, Assignments

This release is focusing on the testing, validation and usability of the
equation library contributed by Jean Wilson. To that effect, it introduces a new
kind of objects, assignments, that only exist on the DB48x and have no direct
equivalent on original HP calculators. It also completes the support for library
equations in the `Root` command.

Here is an example that illustrates these capabilities, testing the
`Ohm’s Law & Power` equation in the library:

```rpl
V=240_V  I=32_A
@ Expecting [ R=7.5 Ω P=7 680. W ]
'ROOT(ⒺOhm’s Law & Power;[R;P];[1_Ω;1_W])'
```

If you are reading this release note directly on the calculator, you can simply
click `ENTER` while the text above shows up, and it will be copied in your
editor. You can change the values of the input variables to explore various
possibilities.

In this example, `V=24_V` is an assignment object that assigns the value `24_V`
to the global variable named `V`. It is almost equivalent to `24_V 'V' STO V`,
except that the value placed on the stack is the assignment object itself. In
other words, evaluating `V=24_V` places `V=24_V` on the stack. This makes it
easy to edit or evaluate assignments on the stack using the interactive
stack. In particular, you can select an assignment on the stack wiht the
interactive stack and use the `Eval` (F3) function to restore the variable to
the value in the assignment.

The `ROOT` command in the example illustrates how you can directly use equations
in the equation library as argument to `Root`, and use the multiple-equation
solver to solve for more than one variable at a time.

All the examples in the on-line help are now also tested automatically, in order
to ensure that all the given examples give the expected results.

### Features

* Implement `CustomMenu`, whicih is toggled by successive presses on the _VAR_
  key. An example is shown in the `Demo.48s` file. The content of the `CST` or
  `CustomMenu` variable is used to define this menu.
* The documentation now contains numerous executable examples.
  These examples are identified by a Markdown code block with the `rpl`
  syntax colorization indicator. They can be executed directly from the
  on-line help on the calculator by hitting ENTER while the code block is shown
  on the screen.
* The test suite automatically tests all the documentation examples.
* Two new equation sets, `Light Propagation` and `Ultrarelativistic Cases`
* Four new equations in `Energy & Momentum` equation set
* Assignment objects in the form `Name=Value`, e.g. `A=3`.
* The solver now emits assignment objects for the solution
* `▶` command to store while keeping value on stack. As an extension relative to
  the HP50G, this command also works inside RPL algebraic expressions.
  For example `3▶A` stores `3` in `A` and returns the value in `A`.
  The command is called `Copy` (the HP50G ARM calls it _▶ (Store)_)
* The `Root` command now accepts library equations as input.
* Arrays and lists are now accepted in algebraic expressions, using `;` as
  a separator between values. For example, `'[1;2;3]+[4;5;6]'` adds two vectors
  using an algebraic notation. Vectors can contain algebraic expressions. For
  example `'[x+1;y+2;z=3]'` is a valid vector expression.
* The solver now accepts algebraic input, including for the multiple equation
  solver using vectors as input.
* Ad `RombergPlot` example to Library and Demo file. This example shows how the
  `Integrate` command evaluates the underlying function.
* menus: Add `XRng` and `YRng` to the `PlotMenu`

### Bug fixes:

* Fix a sign bug in the `Simple Slope` equation
* Fix "Too many open files" error while saving constants, xlibs or equations
* Avoid infinite loop for unterminated `case` statement
* What follows a unit in an algebraic expression is no longer ignored.
  `'330_m-20_m'` was incorrectly interpreted as `'330_m'`, now is `'310_m'`.
* Fix and document the `Integrate` imprecision and iteration settings.
* text: Respect display settings in `→Str`. For example, `3 FIX 0.1 →Str` now
  returns `"0.100"` and not `"0.1"`, like on HP calculators
* Repair parsing of HP-style complex numbers, e.g. `(12;3)`
* Refactoring of object insertion in text editor to fix various bugs,
  including the `Echo` command in the interactive stack inserting the object at
  the end of the text editor instead of at the cursor position.
* Do not issue `Invalid digit for base` on the console parsing `1E-10`
* Fix null-dereference issue in `to_decimal_if_big`, which could be triggered if
  interrupting an `Integrate` command using the _EXIT_ key.
* Avoid occasional garbage at right of menu area
* simulator: Ensure Copy correctly quotes equations
* Move image for _E Field Finite Line_ to right section

### Improvements

* Add references to keyboard overlays in the documentation
* Add documentation for the `Root` command
* Improve the way we generate the image files in the Makefile
* Improve solver behaviour when a solution is not found. Notably, the solver is
  more likely to converge towards an extremum.


## Release 0.8.1 "Sale" - Multi-equation solver

### Features

* Multiple-equation solver (HP's MES), solves for variables one at a time
* The `|` operator (aka `where`) applies to library equations
* The `|` operator respects variables with units in expressions
* simulator: Add support for copy and paste (to/from simulator)
* Add support for cylindrical and spherical 2D and 3D vectors
* Positional graphic combination operations (e.g. `GraphicRatio`)
* Switch to Greek or Cyrillic keyboard maps based on character menu
* Add EDIT menu commands to transient alpha (e.g. ▶F3 is Word→)
* Index the  help file for performance (about 5x faster on DM42)
* Accept verbatim code and RPL code snippets in the help file
* Parse and show help topics  taking all aliases into account
* Convert lists and equations to RPL programs with `→Program`


### Bug fixes

* Show tagged values for vectors and matrices
* Update the target global variable after running `root`
* Show all variables in the `SolvingMenu` (with a settings to control it)
* Unit-related commands accept tagged objects and expression-enclosed units
* Add angular units (e.g. radians) in angular equations
* Correct unit for `V` in `Cantilever Shear` (was `n` instead of `N`)
* `Purge` now correctly restores UI patterns settings
* Add missing font parameter to `→Grob` (HP calculator compatibility)
* Include equations and xlibs to list of symbolic objects
* Fix precision loss for `atan`, `acos` and `asin` for some values
* Add angles for `atan2` when using hardware-accelerated floating-point
* Remove spaces and separators in the names of library equations
* keyboard: Replace ASN with ->NUM
* Preserve trailing decimal separator in `FIX` mode with `NoTrailingDecimal`
* Fix backspace and delete operation around number separators
* Fix the definition of `cosh` for complex values (was computing `sinh`)
* Accept uppercase and lowercase `.48s` when saving/restoring state
* Accept both `Ω` or `Ω` as spellings for Ohm (different Unicode)
* Only update the state file when disk operations are successful


### Improvements

* Add `arcsin`, `arccos` and `arctan` spellings
* solver: Reorganize solver code
* documentation: Udpate equation documentation with examples
* Save UI patterns as hexadecimal numbers (also in `Modes` command)
* Use only tabs in library.csv
* Keep cursor at end of buffer when moving through history with word right
* Clear selection when BSP is used with a non-empty selection
* Ensure `debug_printf` always refreshes the screen
* Switch to binary search for command parsing (~100x faster)
* Rename some statistical functions for consistency
* Fix the list of authors in the online help
* doc: Update performance data


## Release 0.8.0 "Gabriel" - Symbolic operations, equations and library

This release adds symbolic integration, differentiation and equation
solving, delivers an extensive equation library, and improves the
library feature to enable large library objects to be defined in
separate files and optimize execution speed for library items.
It also improves the rendering of complex equations and fixes a number
of crashes or user-interface problems.

### Features

* Symbolic integration, `Primitive` command, `'∫X(sin(X))'` syntax
  `'∫X(sin(2*X+3)-X)'` evaluates as `'-cos(2*X+3)/2-x²/2'`
* Symbolic differentiation, `Derivative` command, `∂X(sin(X))` syntax
  `'∂X(sin(2*X+3)-X)'` evaluates as `'2·cos(2*X+3)-1'`
* Symbolic equation resolution, `ISOL` (`Isolate`) command
  '`sin(2*X+3)=A' 'X' ISOL` gives `'X=(sin⁻¹ A+2*i1*π-3)/2'`
* Apply arithmetic and functions on both sides of equations like `A=B`
  `'A=B' sin 1 +` results in `'sin A+1=sin B+1'`
* Add possibility to define library objects in separate files
  The various demos from previous releases are now also in the library
* commands: Add `→Prog` command to convert expressions to RPL programs
  `'sin(2*X-Y)' →Prog` gives `« 2 X × Y - sin »`
* Accelerate evaluation of library entries
  Invoking a library object is as fast as if it was on the stack.
  Notice that this is faster than global objects that require lookup.
* Add ``Obj→` support for user-defined function calls
  `'F(A;B;C)' Obj→ DROP Obj→ ` gives `[F A B C]`.
  The first call to `Obj→` expands the expression, leaving an isolated
  function call on the stack, which the second `Obj→` expands.
* Automatically convert polynomial objects to expressions when needed
* Many improvements to the equation library contributed by Jean Wilson
* Document the equation library variables in the help file
* Add classical/relativistic Kinetic Energy comparison demo
  This was suggested by Jean Wilson as an illustration
* parser: Parse and convert HP syntax for `|`
  Typing `'A(X;Y)|(X=1;Y=2)'` converts to `'A(X;Y)|X=1|Y=2'`

### Bug fixes

* Improve graphical rendering of some complex expressions
* Render `sqrt` as `√` and not `squareroot` in HP compatibility mode
* Do not draw parentheses around `|x|` when rendering `abs`
* Redefine `rpm` as `turn/min` (unit consistency of rotational speed)
* Avoid crash in `for` loop if termination condition fails to evaluate
* Fix rendering and saving of directories
* Do not leave incorrect stack content when running `Obj→` on text
* Make size consistent in vectors containing tagged objects
* Accept tagged objects as input in algebraic functions
* Avoid parsing error for `1,234` when `.` is the decimal separator
* Debug output related to expressions is no longer labelled "equations"
* Fix unit error in Drift Speed & Current Density
* Cut the size of the build version ID to avoid DMCP buffer overflows
* Avoid possible corruption when an error occurs in a program
* Improve error messages for file errors, e.g. when loading a state
* Move cursor at correct position after numbers when entering units
* Reject multiple consecutive units, e.g. `1_m_s`
* Fix issue where we insert `=` incorrectly on the command line
* Address simulator warning about potential buffer overflow

### Improvements

* tests: Add tests for the newly added library entries
* primitive: Add test suite for symbolic integration
* tests: Add test suite for symbolic differentiation
* Factor out code to expand objects on the stack
* `make install` now Installs from distribution files
* demo: Reorganize demo files as directories
* tests: Add test for `Obj→` on various object types
* tests: Factor out code checking state of the complete stack
* tests: Avoid emitting something that looks like compilation errors
* Update demo file
* Improve definition of atomic mass unit, add `Da` (Dalton) alias
* expressions: Optimize the way to split an equation
* tests: Adjust tests after changes in `SymbolicMenu`



## Release 0.7.18 "Who" - Subst, Where, Apply

This release implements the `Apply`, `Subst` and `|` (`Where`) commands.

### Features

* ui: Allow Shift-SPC to enter `=` in an expression
* Implement `subst` and `where`
* Implement the `Apply` command
* Implement the `EQNLIB` command
* Add `CONSTANTS` as a way to select mathematical constants menu
* Add `CONLIB` as an alias for `ConstantsMenu`.

### Bug fixes

* solver: Adjust detection of "epsilon" for large values
* ttf2font: Flip x coordinates for dense fonts

### Improvements

* doc: List commands that will never be implemented


## Release 0.7.17 "Open" - DoSubs, DoList, entering units

This release adds `DoSubs`, `DoList`, `NSub` and `EndSub` commands, and fixes
related issues that were found with the associated examples in teh HP50G
Advanced Reference Manual.


### Features

* lists: Implement `DoList`, `DoSubs`, `NSub` and `EndSub`
* units: Add usual "big" units to `Computing` units menu (e.g. KB, MB)
* graphics: Add `Freeze` command
* ui: Make it easier to enter units
* expressions: Accept algebraic forms for `integrate` and `root`
* expressions: Graphical rendering of integrals

### Bug fixes

* case: Preserve the code for the default case (which was lost before)
* parser: Parse arg-less alegbraic commmands such as `NSub`
* equations: Fix syntax errors in built-in equations, e.g. missing parentheses
* equations: Replace variables that match DB48X command names, e.g. `Re`
* equations: Replace imperial units with SI units, e.g. `in` with `cm`
* units: Reject user-defined functions in unit expressions
* constants: Fix definition for the `qε0` constant

### Improvements

* Update help about equations with some additional material
* tests: Run through all the builtin equations
* ui: Do not insert an extra space before parentheses in equation
* simulator: Add macOS icons for DB48X and DB50X
* font: Record saved font with `v` update


## Release 0.7.16 "Clean" - New commands

The focus of this release is on new commands, notably for matrix and vector
operations. This release also ships with a DM48X-specific keymap, which fixes a
problem with teh file selector on the DM32. The equation library has been extended with numerous equations, but they are not fully validated yet.

### Features

* `con`, `idn` and `ranm` matrix generation commands
* `Array→` and `→Array` commands to convert array to/from stack
* `dot` product and `cross` product commands for vectors
* `DispXY` styled text rendering command
* `DupDup` command duplicating top item twice
* Add a large number of equations to equation library

### Bug fixes

* Fix `decimal::to_bignum` for small magnitudes
* Return angle unit for `atan2` and `arg` commands
* The `for` loop on lists no longer ends leaving the debugger active
* Interactive stack `DropN` command returns to level 1
* Fix file selector's "New file" on DM32 so that ENTER terminates it
* A few fixes in equations in the equation library


### Improvements

* Improve graphical rendering of expressions such as multiplication operators
* doc: Update status
* font: Fix `v` glyph vertical placement, add dot and cross glyphs
* ttf2font: Add additional verbose info about source data
* Add `CONSTANTS` as an alias for `ConstantsMenu`
* Replace documentation references to `EEX` with `×10ⁿ`
* Optimize parsing of real numbers in parentheses


## Release 0.7.15 "Teaching" - Bug fixes notably on iOS

This release mostly focuses on issues exposed by the iOS releases.
It's a bug-fixes only release.

### Bug fixes

* ios: Fix a screen refresh bug delaying the display of computation results
* ios: Increase user-accesssible memory for DB50X to match the DM32
* files: Avoid opening two files when a loaded file contains units/constants
* units: Restrict unit expressions further, e.g. forbid `1_km^s`
* build: Do not add unwanted macOS-specific files in release tar files
* build: Remove irrelevant help file from releae tar file
* constants: Fix numerical value for G constant
* tests: Rename `M` demo helper to `D`, since we use `M` in symbolic tests
* makefile: Add `mv` echo to targets doing image comparison
* units: Use pi constant in definition of radians unit
* parser: Detect syntax error on `(inv(x))` in non-expression mode
* units: Avoid infinite loop for bad unit exponents
* files: Avoid crash in `file_closer` if file does not exist
* tests: Add DMS/HMS operations to math demo
* tests: Add keyboard shortcuts to launch the demos


## Release 0.7.14 "Kids" - Equation-related bug fixes

This release fixes a number of issues that were discovered primarily through the
Columns and Beams equations.


### Features

* trigonometrics: Add conversion from non-standard angles, so that `cos(1_turn)`
  gives the correct result.
* debug: Debug on error with `DebugOnError` and `KillOnError` settings. This
  makes it easier to debug an RPL program, by making it possible to single-step
  around the instruction that generated the error.
* tests: Add three 30 second demo of DB48X features. These are to generate
  marketing videos for the iPhone version on the Apple store (to be done).


### Bug fixes:

* ui: Keep a GC pointer in `draw_object` to avoid a memory crash
* equations: Add missing units in some equations, e.g. `I` and `A` in second
  equation of Coilumns and Beams
* equations: Add explicit `radian` unit in Eccentric Columns `cos`, which
  ensures we get the correct result from the HP50G manual even when in Degrees
  mode.
* units: Correctly factor out non-integral powers, so that we can compute
  `1/sqrt(epsilon_0*mu_0)` and get the correct result.
* catalog: Display commands that begin with selection first, so that `FORE`
  shows `Foreground` before `AlphaForeground`.
* stats: When computing a sum, evaluate the expression on all terms. The result
  for `Variance` with single variables was wrong because the first term was
  computed incorrectly due to a misguided optimization.
* graphics: Error out in `RGBPattern` for negative input. The negative values
  were generating an error, but it was not reported, so the next command was
  likely to report it.
* help: Render shift keys correctly in the color version. The bitmap was
  interpreted as containing color data. Colorize it instead.

### Improvement

* ui: Select orange as background color during search. The previous setting of
  showing seardch using white foreground on a white background was probably
  pushing the notion of "blind search" a bit too far.


## Release 0.7.13 "Murderers" - Solver improvements

This releases focuses on improvements to the solver, with the completion of the
Columns and Beams section from the HP50G equation library.

### Features

* equations: Add remaining equations from "Columns and Beams"
* loops: For loops on lists and arrays
* menus: Add `R→D`, `D→R`, `→Polar` and `→Rectangular`
* menus: Automatically select tools menu for library equations
* units: Allow `ubase` to work on expressions
* units: Graphic rendering of units


### Bug fixes

* 48calc.org: Fix mouse click position
* `#ABC #DEF -` now correctly produces a based number with >64-bit wordsize
* conditionals: Parse and evaluate `IFTE` correctly
* equations: Fix Elastic Buckling
* files: Avoid crash in `file_closer` if file was not open
* istack: Enable Swap feature on top two levels
* menu: Update SolvingMenu when updating VariablesMenu
* parser: Deal with negation more "normally", parse `-a²` correctly
* solver: Compute units correctly for inputs
* solver: Do not change unit when storing in a solver variable
* solver: Emit correct error message in `EvalEq` if missing variables
* solver: Preserve errors reported by underlying function
* units: Do not evaluate/render units with names
* units: No longer read variables `m` and `s` while processing `1_m/s`
* units: Simplify units that convert to real numbers


### Improvements

* Update .gitignore
* build: Add BMP files to the distribution
* complex: Optimize exit conditions for parentheses
* solver: Add test for equation library
* solver: Add tests for solving with units
* solver: Improve behaviour of `EvalEq`
* solver: Keep units and constants as-is in equation
* solver: Make precision relative to equation sides magnitude
* stack: Show vectors vertically by default
* ui: Do not persistently hide stack with current equation
* units: Keep power integral, i.e. avoid getting `1_m^2.0/s`
* units: Strip tags from unit conversion functions
* units: The `EvalEq` command should not evaluate dates
* wasm: Add logos to the repository



## Release 0.7.12 "Multiply" - Multiple equations

This release focuses on the equation solver, notably in interaction with the
equation library. The goal is to get one step closer to the equation library in
the HP50G, including the ability to have graphical illustration and multiple
equations.

### Features

* doc: Add documentation for the equation library
* doc: Add images from HP50G equation library (to be used later)
* doc: Some help for the elastic buckling equations.
* equations: Accept lists of equations in library
* help: Add documentation for the various constants
* help: Do not exit help when opening URLs or missing topics
* lists: Add a setting to evaluate list as programs
* menu: Add menu entries for solver imprecision and iterations
* solver: Add support for multiple equation solving
* ui: Add settings to hide/show empty menus and clear menu on EXIT
* units: Add flow units (per user request) in Fluid section of units


### Bug fixes

* blitter: Adjust the right margin
* blitter: Base horizontal adjust on scanline, not width
* characters: Display correct content for built-in menus
* constants: Close current file while parsing values
* constants: Update some outdated values
* doc: Show help for equations and constants
* help: Do not try to load PNG images
* rewrites: Avoid contradictory rules when reordering constants
* solver: Work correctly with units (when in variables but not equation)

### Improvements

* build: Shorten the size of the version abbrev
* config: Use config files only for user configuration
* doc: Record performance data about unit conversion
* help: Avoid slowing down when scrolling through pages of help
* help: Record position for history even without a `\n`
* simulator: Add tweak to show RPL object details
* tests: Increase wait time for tests with blinking cursor
* units: Do not simplify while in unit mode


## Release 0.7.11 "Rest" - Refine interactive stack, graphics in help

This release is a refinement minor release. The primary focus is the interactive
stack, which now lets you edit items, sort either according to memory
representation or by value, display information about objects, and jump directly
to a given stack level using digits.

The simple random number generator implemented in 0.7.10 was replaced with an
additive congruential random number generator (ACORN), which can be configured
in number of bits and number of iterations. A side effect is that there is now
regression testing for single-variable statistics.

The history feature was also improved by automatically enabling the `EditMenu`
when selecting history, and then having the (unshifted) word left and word right
commands automatically cycle through history if used at beginning or end of the
editing buffer.

### Features

* help: Add ability to display BMP images in help files
* images: Convert help images to BMP
* ui: Add `Edit` feature to interactive stack
* ui: Add history menu entries to `EditMenu`
* ui: Accept `UNDO` while in interactive stack mode
* ui: Have word previous/next cycle through history
* ui: Accept digits to select stack level in interactive stack
* random: ACORN random number generator

### Bug fixes

* editor: Fix spacing after number followed by `-` sign
* ui: Do not set the `editing` field from interactive stack
* ui: Replace interactive stack "Edit" with "Echo"
* ui: Block user input while using interactive stack
* ui: Do not draw menu markers when displaying interactive stack
* runtime: Avoid crash running above allocated memory in `move_globals`


### Improvements

* ui: Reorganize code handling interactive stack keys
* help: Adjust help area to new height for menus


## Release 0.7.10 "Hospitality" - Interactive stack

This release primarily adds the "interactive stack" feature of HP calculators.

### Features

* stack: Interactive stack and associated menu
* functions: Very basic random number generator
* demo: Add `CountPrimes` and `RandomPlot` examples

### Bug fixes

* menus: Do not execute if-then-else and similar
* expressions: Avoid error testing for zero/one in power operator
* condidionals: Avoid infinite loop evaluating condition
* menu: Insert `iferr-then-else` correctly from menu
* constants: Skip menu entries

### Improvements

* menus: Reorganize stack menu to put `Dup` and `Drop` on first page
* menu: Add error functions to `Debug` menu


## Release 0.7.9 "Just Asleep" - Online WASM simulator

This release includes a number of bug fixes, facilitates build from scratch by
third-parties, and delivers a WASM-based simulator that runs on the
https://48calc.org web site.

## Features

* menu: Add `Purge` to the `ClearThingsMenu`
* purge: Add support for lists
* units: Accept units for `sqrt`, `cbrt` and `xroot`
* wasm: Add variant for `48calc.org`
* wasm: Implement WASM support

## Bug fixes

* complex: Give `Syntax error` for phasor without an angle
* dms/hms: Parse empty numbers in DMS entry
* dms/hms: Protect display against bad input
* editor: Make sure we reposition after shift-up and shift-down
* parser: Parse degrees as an angle unit in phasors
* simulator: Avoid high CPU usage when a timer is active
* simulator: Use the correct color for firmware text
* ui: Compute the correct refresh rate even when nothing is displayed
* ui: Create a non-empty dirty rectangle when clearing annunciators
* ui: Do not refresh beyond LCD size
* ui: Ensure we redraw the shift region to clear busy
* units: Disable simplification during unit definition evaluation

## Improvements

* build: Fix the clean build
* object: Remove defaults for `as_uint32` and similar
* parser: Cache parser::length when possible
* parser: Merge the `parser::end` and `parser::length` fields
* parser: Optimize integer parsing early exit
* simulator: Avoid `Cancel` in file save dialog
* simulator: Use `https` as a protocol for git submodules
* tests: Add support for degrees sign
* tests: Add test for polar angle conversion.
* units: Add `factoring` variable to limit simplifications
* wasm: Add link to deployed WASM simulator in the README
* wasm: Add script to add COOP / COEP headers
* wasm: Run the RPL thread in a separate thread


## Release 0.7.8 "Mustard" - Constants in equations

This release keeps marching towards full support for an equation library.
The primary focus was support for constants in equations, including constants
with units like the speed of light, as well as fixing various user-reported
issues.


## Features

* cycle: Apply to value of tagged object
* equations: Add units to built-in equations
* equations: Adjust menu label to remove units
* equations: Strip units but not constants when rendering
* expressions: Treat `2X` as an implicit product
* solver: Strip units from constants
* units: Unit prefix should preserve the tag

## Bug fixes

* clearlcd: Fix erasure of screen when not in graphics mode
* constants: Count number of menu entries correctly for builtin menus
* decimal: Accept leading `.` or `,` for decimal values
* expressions: Parse negation after parentheses
* sum: Do not accept a non-name in a sum or product
* type: Return a type value for decimals
* ui: Fix insertion/editing of infix with alphabetic names
* units: Do not read units from variable if they exist
* xroot: Reverse `xroot` arguments in algebraic parsing

## Improvements

* editor: Shuft-up returns to beginning of line if on first row
* errors: Add `error_save` class, use it in `constant::value`
* expressions: Use the `SaveAutoSimplify` class in `simplify_products`
* units: Split `Eng` to `Elec` and `Visc`


## Release 0.7.7 "Forgiving" - Units in equations

This release keeps marching towards full support for an equation library.
The primary focus was support for units in equations.


### New features

* solver: Accept equations in solver menu
* solver: Add shortcut to solve an equation from the library
* solver: Display the current equation above the stack
* solver: Solve expressions containing units
* solver: Add units for solver variables when entering them
* equations: Add option to list variables with units
* programs: Enforce numerical values for solver / plotter
* constants: Implement programmatic lookup
* fonts: Add support for fixed-width digits
* keyboard: Interpret `ASN` as `AsNumber` (convert to decimal)
* complex: Allow insertion of angle while entering phasors
* complex: Implement auto-complex promotion
* graph: Render abs(X) with bars (e.g. |X|)
* functions: Automatic simplification of expressions


### Bug fixes

* arithmetic: Avoid null-dereference in complex operations
* help: Close help file if topic not found
* solver: Do not store tag for tagged values
* graph: Gracefully fallback if fraction integral part does not render
* units: Avoid null-dereference if unit simplification fails
* units: Count parentheses while parsing units
* put: Fix null-dereference checking the index
* fractions: Do not render two negative signs in graphical mode


### Improvements

* cycle: Update behaviour for several data types
* menu: Replace `abs` with `|z|` in complex menu
* ui: Micro-optimization to avoid reading object type twice
* parser: Accelerate and improve object parsing
* recorder: Add recorder entries for evaluation
* build: Remove any leftover references to Intel decimal library
* tests: Add `▶` entry in tests
* tests: Increase default wait time to 1000ms
* tests: do not error out if `teval` takes less than 100ms
* equations: Rename `PerfectGas` equation to `IdealGas`
* menus: Adjust size of menus to make descenders visible
* solver: Replace `SolverPrecision` with `SolverImprecision`


## Release 0.7.6 "United" - Equation Solving Menu

This release is primarily about implementing a dynamic solving menu that makes
it easier to solve equations with multiple variables. This is roughly equivalent
to the "Solve Equation" application in the HP50G.

### New features

* solver: Implement solving menu
* tag: Graphic rendering for tagged objects
* lists: Implement `lname` and `xvars` commands
* arithmetic: Implement `div2` command
* variables: Implement `vars` and `tvars` commands

### Bug fixes

* render: Avoid errors while rendering / graphing
* expressions: Avoid consuming stack levels for invalid expressions
* symbols: Avoid ignoring the list of bad characters in symbols
* command: Fix for `x!` parsing
* stack: Correctly set clipping for stack index
* doc: Fix typo in release note

### Improvements

* menus: Add `PixOn`, `PixOff`, `Pix?` and `PixC?` to `GraphicsMenu`


## Release 0.7.5 "Perfect Joy" - Polynomials and symbolic rewrites

This release contains a lot of groundwork in preparation for future work on
symbolic expressions, symbolic solving and symbolic integration, as well as to
improve compatibility with HP calculators. In particular, `rewrite` has been
replaced with the HP equivalents, `↑Match` and `↓Match`, allowing top-down and
bottom-up replacement, as well as support for conditions. Also, these commands
return the number of replacements performed instead of just `0` or `1`.

THe other major user-visible new feature is the addition of a polynomials data
type, which does not exist on HP calculators, exposing polynomial features in a
way that is more consistent with the spirit of RPL. For example, Euclidean
division of polynomials can be achieved using the regular `/` operation on
polynomials instead of requiring a dedicated `DIV2` command.


### New features

* Support for polynomials as a data type, including Euclidean division
* Arithmetic operations on polynomials, including `sq` and `cubed`
* Conversion functions `→Poly` and `Poly→` to convert to and from polynomials
* Optional case-sensitive symbol matching
* Algebra configuration directory (like `CASDIR` on HP calculators)
* rewrites: Replace `rewrite` command with HP-compatible `↑Match` and `↓Match`
* rewrites: Add `ExplicitWildcards` option to match HP syntax (`&A`)
* rewrites: Add rules to expand powers
* rewrites: Add support for conditions when matching patterns
* rewrites: Add support for step-by-step rewrites
* rewrites: Add support for bottom-up rewrites
* flags: `Purge` now resets system flags to default value


### Bug fixes

* editor: Fix unresponsive keys after using `EXIT` key while searching
* complex: Avoid emitting syntax errors while parsing
* rewrites: Avoid potential garbage collection corruption problem
* rewrites: Disable auto-simplification during rewrites
* rewrites: Factor out rewrite loop
* expressions: Encode expressions with type ID >= 128 correctly
* arithmetic: Add space around `mod` and `rem` in rendering
* graph: Do not add parentheses for `X*(Y/Z)`
* functions: Make percentage operations binary functions
* functions: Turn `min` and `max` into algebraic functions
* cycle: For expressions, cycle graphic/text rendering correctly
* menus: Replace `EquationsMenu` with `ExpressionMenu` in other menus
* ui: Insert space when inserting array inside function


### Improvements

* menus: Updates to `PolynomialMenu` to enter polynomials and for conversions
* menus: Add product and sum to symbolic and algebra menus
* menus: Make `ToolsMenu` select `SymbolicMenu` for symbols
* expressions: Reorganize the code for rewrites
* rewrites: Add recorders for rewrites that are actually done
* tests: Some adjustments on color images
* rewrites: Convert algebraics into expression as needed
* complex: Parse `3i` and `i3` in addition to `i`
* tests: Add support for more characters
* simulator: Separator color and dm32 support
* graph: Add space when rendering simple function
* keyboard: Updated SVG files with latest menu labeling changes



## Release 0.7.4 "Flesh" - Polishing and refinements

This release is mostly about polishing various aspects of the
implementation to make it more convenient and more efficient. It also
adds user-defined functions parsing and evaluation, pixel-manipulation
commands, bit operations on binary numbers, memory operations like
`sto+` or `incr`, loading and saving BMP files, color support in the
simulator, and more.


### New features

* editor: Implement configurable word wrapping
* expressions: Add code for n-ary functions like `sum`
* expressions: Parse user-function calls like `F(1;2;3;4)`
* expressions: Ensure funcall objects are evaluated immediately
* functions: Add `sum` and `product` functions
* functions: Add combinations and permutations
* functions: Implement number rounding operations (`rnd` and `trnc`)
* graph: Add graphical rendering for `cbrt` (cube root) and `xroot`
* graph: Graphical rendering of combinations, permutations
* graph: Graphical rendering of sum and product
* graphics: Add `pixon`, `pixoff` and `pix?` commands
* graphics: Store and recall BMP files with `sto` and `rcl`
* graphics: `ToGrob` command converting object to graphic
* logical: Add `SetBit`, `ClearBit` and `FlipBit` commands
* memory: Implement the `Clone` (`NewOb`) function
* menus: Add `log2` and `exp2` to `ExpLogMenu`
* menus: Place `ListMenu` as a keyboard-accessible menu
* parsing: Parse n-ary functions
* program: Add vertical program rendering mode
* stack: Display error message emitted during stack rendering
* ui: Add colorization parameters for the user interface
* ui: Add some colorization
* variables: Add `Sto+`, `Rcl+` and other variable arithmetic
* variables: Implement `Increment` and `Decrement`


### Bug fixes

* decimal: Fix precision when computing gamma/lgamma
* decimal: Fix rounding bug when rounding increases exponent
* doc: Add missing dependencies on Fedora (submitted by @vkadlcik)
* files: Do not error when opening constants/equation/library files
* files: Open only one configuration file at a time
* graphics: Fix bug drawing a line of width 0
* graphics: Use foreground color for parenthese and ratio
* lists: Separate list sum/product from regular sum/product
* renderer: Make sure `printf` respects target buffer size
* simulator: process double-clicks correctly (submitted by @kjellc)
* tests: Change the height of ignored header


### Improvements

* command: Factor out arity for all commands
* constants: Report parse error location for invalid constants
* demo: Add HP-48 style slow walk to `Walk` demo
* demo: Modernize the code a little
* demo: Modify performance benchmarks to use `TEval`
* demo: Replace imaginary unit constant
* doc: Remove reference to Intel Decimal Library
* files: Convert all file names to lowercase (Linux support)
* functions: Make it possible to interrupt a running sum/product
* graph: Improve rendering of `exp`, `exp2`, `exp10`
* graphics: Separate color conversion step
* help: Do not display command name while editing
* ids: Make room for a few additional 1-byte commands
* locals: Document the absence of compiled local variables
* makefile: Add configuration files to the release `.tgz` file
* parsing: Make the error message for sub-expressions more local
* readme: Remove reference to DM42 from top-level readme
* simulator: Avoid crash rendering %t in recorder
* simulator: Convert simulator code to support color
* simulator: Replicate open files limitations
* simulator: Separate db50x and db48x builds
* tests: Add colorized images to testing
* tests: Avoid occasional errors on some long-running tests
* ui: Define cursor position in `SelfInsert` with `\t`
* ui: Ignore EXIT, BSP and ENTER keys when clearing error


## Release 0.7.3 "Perfume" - Mostly bug fixes

This release is mostly about bug fixes, improving the build on simulator, and accelerating the test suite while keeping it stable.

### New features

* simulator: Add F8 key to save state in the simulator
* errors: Add a beep when an error is shown
* linux: Add `-s` option for screen scaling (when Qt gets scaling wrong)
* equations: Get library equation value for plotter, solver and integrator
* characters: Add constant, equation and lib markers to RPL menu
* characters: Add music-related characters and character menu
* commands: Add missing stack commands (nip, pick3, ndupn, unrot, unpick)


### Bug fixes

* variables: Clone purged objects on stack after `Purge`
* units: unit * symbolic is preserved as is (e.g. `'A'_m`)
* compare: Enforce the `NumericalResults` flag for comparisons
* constants: Fix parsing of constants, equations and library items
* sto: Repair `file exists` error storing to a source file
* simulator: Do not try to create directory if it exists
* Report file errors, e.g. permissions or I/O errors
* equations: Mark `c` and `R` as constants in equations
* simulator: Double clicks are now considered as virtual keyboard touches
* ui: Emit only one beep, not two, for a syntax error on the command line
* ui: Avoid rare null-dereference crash when menu label is not set
* complex: Report a syntax error if the second half is empty
* utf8: Do not accept constant/equation/library codepoint in names
* units: Multiplying by `1_m` is OK even with algebraic
* tests: Avoid case where CLEAR does not clear errors
* audio: Improve audio reliability on the simulator
* linux: Rewrite the audio-generation code to avoid crashes
* linux: Avoid infinite recursion in the tests
* linux: Fix warnings about unused variables
* linux: Avoid warnings about null pointer in strcmp
* linux: Avoid build error due to bad `ularge` overload in settings
* linux: Fix type issue for the Insert function (reported as a warning)
* linux: Remove warning about mixing enums and integers
* linux: Avoid error on printf format
* linux: Avoid warnings about type qualifiers
* linux: Remove warnings about incompatible function casts
* linux: Address warnings about missing initializers
* linux: Fix warning about prinf formats
* linux: Address warning about signed vs unsigned
* linux: Remove warning about fall-through switch statement
* linux: Remove warnings about unused arguments
* tests: Repair several tests that were unstable due to scrolling images
* tests: Increase memory size to avoid occasional out of memory failures
* object: Make `as_uint32` and `as_uint64` consistent for negative input


### Improvements

* ui: Emulate HP48/HP50G behavior for errors (do not require key to continue)
* simulator: Add I/O wrapper around file state save/restore
* dmcp: Remove double return in the code
* simulator: Accept numeric keys in DMCP menus
* doc: Add Kjell Christenson to list of authors
* tests: Run command-line tests silently
* tests: Clear settings the fast way for quick tests
* dmcp: Do not treat the buzzer as a recorder error (avoid message noise)
* simulator: Ensure error messages show up in a recorder dump
* tests: Increase memory size to avoid failing tests
* tests: Increase delay waiting for function plots to appear
* tests: Refactor test suite interaction with RPL thread to accelerate it
* tests: Add a delay before launching the test thread to load initial state
* tests: Add missing reference picture for `char-menu`


## Release 0.7.2 "Light" - Libraries, Characters menu

This release introduces four relatively significant features:

1. An Equation Library
2. A more general Library
3. Character menus
4. A character modification catalog

There are also a number of bug fixes and improvements.


### Features

* The *Equation Library* is similar in principle to what is found in the HP50G.
  It is intended to store equations covering a variety of topics.
  The Equation Library is accessible using the _EQS_ key (🟦 _'()'_).
  It is presently only very sparsely populated, but a future release should
  add the equations listed in Chapter 5 of the *HP50G Advanced User's Reference
  Manual*. Elements of the Equation Library appear as named *Equation Objects*.
  The Equation Library is configured by file `config/equations.csv`.

* The *Library* is similar to the Equation Library, but for all kinds of objects
  such as programs or code snippets. The Library is accessible using the _LIB_
  key (🟦 _VAR_). It can be used to customize your calculator, and is intended
  to play the roles of the `CST` variable (quick access to common features)
  and Library Objects / XLIB (external extensions to RPL). Elements of the
  Library appear as named *Library Objects*.
  The Library is configured by file `config/library.csv`.

* The *Characters Menu* lets you enter Unicode characters easily, by presenting
  various classes of characters, such as `RPL`, `Greek` or `Punct`.
  The Characters Menus is accessible using the _CHAR_ key (🟦 _2_).
  It can be used to enter international characters (e.g. Greek or Cyrillic), as
  well as special characters such as arrows or blocks.
  The Characters Menu is configured by file `config/characters.csv`.

* The *Characters Catalog* appears when the `Catalog` is active and the cursor
  is inside some text object. It gives you access to characters that are
  visually close to the character on the left of the cursor. For example, after
  typing `A`, the presented choices include `À`, `a` or `α`.
  The Characters Catalog is configured by file `config/characters.csv`.

* compare: Add comparisons for `true` and `false` values

* Add `TEVAL` command (timed evaluation)


### Bug fixes

* Do not add unnecessary parentheses in ratios, e.g. `(A+B)/(X-Y)`
* Make sure we can save back the configuration files correctly
* Improve access path checks to accept `config:constants.csv`.
* Avoid syntax error in `1/(1+x)` due to `1/` being seen as a fraction
* unitfile: Remove slight risk of bad menu display after garbage collection
* date/time: Make sure we save the stack and last args for `Date`, `Time`, ...
* parser: Skip spacing when parsing numbers (to parse back `→Text` result)
* time: Fix rendering of DMS time in lists, matrices, vectors
* catalog: Fix a subtle bug on DM32 leading to a crash using the catalog


### Improvements

* constants: Get values of special `π` and `e` by name
* constants: Add prefix in editor to identify constants, equations and xlib
* constants: Represent constants with an index for memory and performance
* constants: Parse units containing text
* constants: Allow `RCL` to recall a constant value
* units: Direct insertion of units after numbers
* menu: Update `Roll` and `RollDown` menu entries
* show: Show all decimals for decimal values
* help: Display the correct on-line help topic for constants
* catalog: Use less memory for the sorted IDs
* integrate: Use numerical computations for faster convergence
* locals: Improve error message for bad locals
* graph: Improve graphical rendering of constants (bold) and equations
* graph: Do not add unnecessary parentheses in ratios
* tests: Add tests for characters menu/catalog
* tests: Fix the `.` vs `0.` test
* ui: Do not enter DMS inside text
* tests: Display disabled tests in gray
* catalog: Keep a single spelling, e.g. no `add` duplicates
* tests: Add extra delay in the wait for update
* makefile: Add dependency of 'all' to the decimal constants
* save: Improve rendering control when saving files
* stack: Do not save stack in plot, integration or solver
* debug: Disable debugging when launching a program from function key
* simulator: Avoid piling up QT draw requests
* doc: Update performance numbers for 1M loops
* simulator: Add sound support
* simulator: Lazy screen refresh
* dmcp: Add UI refresh callback
* simulator: Move QT-dependent code out of dmcp.cpp
* Add reduced font
* runtime: Various changes to isolate QT build from the rest


## Release 0.7.1 "Whip" - Bug fixes

Inserting variables, constants or units in a program was broken.
Also a few less critical fixes.

### Bug fixes

* decimal: Apply `MinimumSignificantDigits` to `Sig` modes
* tests: Fix missing `]` at end of vector
* ui: Insert commands for unit conversions, constants and variables
* tests: Adjust help screen snapshot for authors
* menus: Do not clip text for hierarchical menus
* constants: Do not use units that don't parse correctly
* dmcp: Day of week convention adjustment
* help: Fix YouTube video preview


## Release 0.7.0 "Temple" - Graphics Equation Rendering

This release introduces a few major improvements, including graphical
rendering of equations and matrices, the `Show` command to display
large objects full-screen, customizable constants, and date-related
operations.

### New features

* Graphical rendering of equations, fractions, matrices, vectors and
  lists. In graphical rendering mode, variables are showin in italics.
* Constants in the `ConstantsMenu`, split into categories, and loading
  from an optional `config/constants.csv` file, in a way
  similar to what existed for units.
* Inverse trigonometric functions (`asin`, `acos` and `atan`) now
  produce unit objects with the current angle mode as a unit. This can
  be configured by the `SetAngleUnits` / `NoAngleUnits` flags.
* `Cycle` (_×10ⁿ_ key) now cycles between angle units.
* `R→D` and `D→R` commands to convert between degree and radian in a
  purely numerical way (no unit). This is for compatibility with HP.
* Add `→Deg`, `→Rad`, `→Grad`, `→πr` commands, which convert a number
  to the target unit using current angle mode, and convert an angle to
  the target angle unit.
* Conversion from DMS to HMS and from HMS to DMS
* Rendering of dates: `19681205_date` renders as `Fri 5/Dec/1968`,
  with a format configuration using the same flags as for the header.
  Note that the date format is `YYYYMMDD`, _not_ the same as on HP
  calculators. This allows `YYYYMMDD.hhmmss` for dates with time.
* `Date` and `Time` command to return the current date and time.
  Additionally, `DateTime` returns both date and time, and
  `ChronoTime` returns the time with 1/100s precision.
* `→Date` and `→Time` commands to set the system date and time
* `Date+`, `DDays` and date arithmetic using `+` or `-`, using day
  units for the results. As an extension relative to HP calculators,
  these will accept fractional days, or other time units. For example,
  adding `1000000_s` to `19681205_date` generates a date with time
  result, `Tue 16/Dec/1968, 13:46:40`
* `JulianDayNumber` and `DateFromJulianDayNumber` commands to convert
  between dates and Julian day numbers. These commands also accept
  fractional input.
* `Show` command showing a full-screen graphical rendering of the
  result on the stack. The resut is size-adjusted. For example, you
  can display all digits in `200!`. If the result does not fit on the
  screen, you can scroll using the _◀︎_ and _▶︎_, as well as _8_, _6_,
  _4_ and _2_. The maximum pixel size for `Show` is set by `MaxW`
  (default is the width of the LCD), the maximum height is set by
  `MaxH` (default is 2048 pixels).
* `AutoScaleStack` and `NoAutoScaleStack` settings to automatically
  adjust the font size for the stack elements.
* Support for system flags -20 to -26 (infinite results, overflow and
  underflow).


### Bug fixes

* simulator: Adjust DMCP month off-by-one error
* Repair insertion of `while` loops and similar commands on the
  command line
* Use stack format when drawing an object with `DrawText` (`DISP`)
* Arithmetic on unit objects no longer auto-simplifies, e.g.
  `1_s 1_s -` returns `0_s` and not `0`.
* Perform computations for `→Q` using integer values, which avoids an
  issue where increasing the number of iterations with an unachievable
  precision could prodduce `1/1` as the fractional result.
* Repair auto-simplification for `i*i=-1`
* Display a negative mixed fraction as `-1 1/3` and not `1 -1/3`.
* Do not insert `()` after a multiplication in algebraic mode
* Accept units and tagged objects in `PolarToReal` and `RealToPolar`
* Accept angle units as input for `→DMS`
* Off-by-one clipping error in header, erasing the shift annunciator
* Fix help for `FC?` (incorrectly stating that it tested for flat set)
* Lookup units and constants in a case sensitive way
* Fix labels for `ExpFit` and `LinFit` in `RegressionMenu`.


### Improvements

* tests: Adjust tests to match bugs fixed in v0.6.5
* dms: Accept entering minutes without third dot, e.g. `1.2.3 ENTER`
* menus: Split the Time, Date and Alarm menus
* Split rendered objects at space boundaries. This notably ensures
  that large numbers are split at digit grouping boundaries, and makes
  it possible to display larger programs on the stack. The rendering
  of programs and matrices/vectors/lists has also been fine-tuned.
* The "white circle" glyph has a thicker border, makes it more
  readable in menus.
* doc: Update the list of unimplemented features
* menus: Draw a white circle for disabled flags, and allow the menu
  function to toggle the flag. This made it possible to reduce the
  number of menu entries for flag-heavy menus.
* Mixed fractions are now the default, as opposed to improper
  fractions
* doc: Improve the quickstart guide
* doc: Improve the documentation for sin, cos and tan
* tests: Make it possible to interrupt a running test
* help: Skip HTML tags, e.g. <video>
* simulator: Add screenshot capability, and reduce window height
* menus: `ToolsMenu` selects time, date or angle menu based on units


## Release 0.6.5 "Testimony": Small bug fixes

This release does not contain much because FOSDEM took a lot of energy.

## New features

* menu: Connect `ceil` and `floor` functions
* Add real to polar conversions
* units: Add `dms` unit to angles menu

## Bug fixes

* decimal: Compute `ln(0.002)` correctly
* integer: Do not parse degree sign if in a complex
* units: Fix parsing of angle units
* font: Add radian glyph


## Release 0.6.4 "Healing": Testing and fixes

This release focuses on heavy testing of the new variable-precision
decimal stack. Adding tests also means finding bugs.

Another significant change is support for fixed-precision
hardware-accelerated floating point, using 32-bit and 64-bit IEEE754
binary floating-point representation. Since this uses a binary format,
some decimal values do not map to decimal correctly. For example,
displaying 1.2 with a large number of decimals will show residue,
because 1.2 does not have an exact (zero-terminated) representation in
binary.

### New features:

* plotting: Make refresh rate configurable
* menu: Add `/` key to `FractionsMenu`
* hwfp: Add support for hardware-accelerated floating-point
* menus: Add hardware floating-point flag to `MathModesMenu`
* ui: Allow multiple uses of `.` to insert DMS separators
* HMS: Editing of HMS values in HMS format

### Bug fixes:

* stats: Fix crash on `variance` with single-column statistics
* algebraic: Clear error before evaluating the function
* functions: Correctly emit a type error for non-algebraics
* ui: Make sure we save stack if closing the editor
* logical: Fix mask for rotate left with 64-bit size
* logical: Make sure we save args for single-argument logicals
* flags: Update flags on `FlipFlag`, consume them from `BinaryToFlags`
* stack: Show multi-line objects correctly
* lists: Returns `Bad argument value` for index with bad arguments
* lists: Return an empty list for tail of empty list
* arithmetic: `→Frac` should not error on integers
* power: Do not shut down during `WAIT` if on USB power

### Improvements:

* menu: Shorten the labels `→QIter` and `→QPrec` to avoid scrolling
* stack: Avoid running same code twice on simulator
* ids: Add aliases for hardware floating point
* functions: Optimize abs and neg
* ui: Replace calls to `rt.insert` with calls to `insert`
* menu: Reorganize fractions menu
* dms: Do the DMS conversion using fractions
* list: Adjust multi-line rendering
* copyright: Update copyright to 2024
* text: Return null text when indexing past end of text

### Testing:

* tests: Increase the delay for help to draw
* tests: Add tests for hardware-accelerated floating-point
* tests: Add shifts and rotate tests
* tests: Check flag functions
* tests: Test DMS and HMS operations
* tests: Add test for `integrate` using decimal values
* tests: Test multi-line stack display
* tests: Add tests for `GETI`
* tests: Min and max commands
* tests: Repair last regression test
* tests: Check behaviour of 0^0
* tests: Avoid string overflow in case of very long message


## Release 0.6.3 "Come and See": Repair test suite

The focus of this release was to reactivate the test suite and fix the
problems that were found activating it.

### New features:

* HMS and DMS operations
* unit: Rendering of `dms` and `hms` units
* Allow `·` as a multiplication sign in equations
* ui: Display 'E' cursor inside parentheses
* graphics: Accept based integers as position for `DrawText`
* complex: Add setting to switch between `2+3i` and `2+i3`.

### Bug fixes:

* decimal: Fix precision loss for addition with carry
* Base: limit range of bases to 2-36
* files: Do not add a trailing zero when reading a text file
* decimal: Adjust `MinimumSignificantDigits` behaviour
* units: Do not auto-simplify `1.0` during conversion
* decimal: Normalize parsed numbers
* solver: Fix sign error in epsilon exponent for solve/integrate
* parser: Accept `x!` as input
* simulator: Avoid faulty break-through in switch statement
* complex: Make tag higher-priority than complex
* editor: Adjust cursor and select correctly during replace
* decimal: Fix display of 0.2 in NoTrailingDecimal mode
* complex: Save `this` in a GC pointer when it can move
* arithmetic: Do not fail because of surrounding error
* decimal: Clamp int32 conversions from decimal
* commands: Parse `exp10` correctly in expressions
* decimal: Avoid infinite loop computing `expm1`
* ids: Do not allow parsing of structures
* dmcp: Make sure the tests don't block on `wait_for_key`
* decimal: Use correct angle unit for negative gamma values

### Improvements:

* settings: Add classes that save/restore a given setting
* Add `XSHIFT` to shift to XSHIFT state directly
* Add NOSHIFT constant to simplify test writing
* ui: Add a variant of `close_editor` without trailing zero
* decimal: Cache gamma_ck values (accelerate gamma and lgamma)
* Replace magic constant `-1` with `EXIT_PGM`
* doc: Record performance data for 1000 iterations of SumTest
* decimal: Add tracing for gamma / lgamma function

### New tests:

* Add tests for arithmetic truncation on short bitsizes
* Add tests for on-line help
* Add test for plotting flags
* Add test for Unicode to text conversions
* Add test for rectangular complex display options
* Add tests for plot scaling functions
* Add tests for the sorting functions
* Add test for parsing text with quotes inside
* Add test for file-based `STO` and `RCL`
* Add test for 2^256 computation (buf #460)
* Fix indentation of `[PASS]` or `[FAIL]` for UTF8 characters
* Add tests for units and conversions
* Add a keyboard test checking the single-colon insert in text
* Add test for i*i=-1 auto-simplification
* Add basic test for numerical integration
* Add test for fraction formats
* Add solver test
* Add missing tests
* Add test for immediate `STO` (#390)
* Add tests for the `Cycle` command
* Add test for catalog feature
* Add test for "smart" keyboard shortcuts introduced in 0.4.6
* Add regression test for #371
* Add tests for editor operations
* Test stack operations
* Add test for `GXor`, `GOr` and `GAnd`
* Add test for `ResetModes`
* Add plotting test for every decimal function
* Add image checking for graphical tests
* Add tests for graphic and text drawing commands
* Make it possible to individually run tests.
* Add plotting tests
* Add test parsing the various spellings for commands

## Release 0.6.2 "Kephas": Restoring the test suite

The focus of this release was to complete the transition to the
variable-precision decimal code. The full regression test suite was
restored, with only two tests still failing (complex `asin` and
`asinh`). The two missing functions, `Gamma` and `LogGamma`, were
implemented. This also exposed many bugs that were fixed.

### New features:

* `NumberedVariables` setting to allow `0 STO` to ease RPN transcoding (#690)
* `ClearStack` (CLEAR) command
* Variable-precision `gamma` and `lgamma` functions (#710)

### Bug fixes:

* Do not leave bad expression on stack after error (#663)
* Reject unit conversion between undefined units (#664)
* Accept names of menus on the command line (#669)
* tests: CLEAR clears stack and errors (#672)
* The `:` characters now starts a tag on empty command line (#673)
* Do not evaluate tagged objects too early (#674)
* test: Entry and editing of equations (#677)
* test: `type` returns negative values in "detailed" mode (#678)
* Run loop end pointer not GC-adjusted for last allocated object (#679)
* Do not erase alpha indicator when clearing busy cursor (#680)
* Do not emit trailing space when rounding `1.999` to `2.` (#687)
* Allow expression rewrites to deal with `pow` (#694)
* Reject `«` character in symbols and commands (#695)
* Rendering of spacing for decimal numbers (#699)
* Improve precision of `atan` function
* Rendering of `+` and `-` operators in compatibility modes (#700)
* Rounding of decimal numbers no longer generates bad characters (#702)
* No longer error out rendering symbolic complex (#703)
* Parse complex numbers correctly inside equations (#704)
* Ensure `sqrt(-1)` has a zero real part (#705)
* Do not drop last digit of decimal subtraction (#706)
* Evaluate expressions during expression pattern matching (#708)
* `LastMenu` executes immediately while editing (#711)
* Add back missing angle glyphs in font (#712)
* Return correct angle quadrant for `atan2` (#715)
* `Get` no longer rejects arrays as index values (#718)
* `Get` returns correct error for bad argument types (#718)

### Improvements:

* Update `.gitignore` entry
* Automated testing of setting flags (#657)
* Automated testing of non-flag settings (#670)
* Test fixed-base based numbers using HP-compatible lowercase notation (#675)
* Test fraction rendering using fancy digits (#676)
* Add test for "compatible" variant of `type` command (#678)
* test: Recover from error during data entry (#681)
* Increase default `MaxNumberBits` to 4096 (#686)
* tests: Add test for cube root of -8 (#685)
* tests: Data entry for `Σ`, `∏` and `∆` (#689)
* Restrict `STO` to names, natural numbers and specific IDs (#688)
* doc: Document flas file access for `STO` and `RCL` (#691)
* list: Optimize iterators to avoid copies (#692)
* tests: spacing-independent testing of structure rendering (#693)
* tests: adjust test suite for variable-precision decimals (#696)
* tests: Automatically exit if `-T` option is given (#697)
* tests: Check we don't accept `.` as meaning `0.` for RPL compatibility
* Add `modulus` alias back for `abs` (#707)
* Improve convergence speed and accuracy for logarithms
* Add `decimal::make` to minimize risk of sign errors
* Display stack level at top of stack level, not bottom (#709)
* Improve complex `sqrt` accuracy on real axis (#714)
* tests: Test decimal functions at full 34 digits precision (#716)
* Complex `sqrt` and `cbrt` with full precision (#717)
* tests: Take into account additional expression simplifications

## Release 0.6.1 "Happy New Year": Quick bug fixes

A few quick bug fixes that make DB48X a bit more usable.

### New features

* Setting to display `2+i3` instead of `2+3i` (#660)
* HMS and DMS operations (#654)
* Special `1_dms` and `1_hms` units rendering in DMS / HMS (#650)

### Bug fixes

* Improve behavior of `+/-` key while editing (#658)
* Do not accept base 37 (#656)
* Insert `for` statement in program instead of executing it (#655)
* Hide trailing decimal separator for decimals with integer values (#653)
* Fix display of `19.8` with `0 FIX` (#652)
* Implement true decimal to integer conversion (#648)

### Improvements

* doc: Record performance data for 0.6.0
* doc: Udpate status file

## Release 0.6.0 "Christmas": Introducing variable precision

This release was a bit longer in coming than earlier ones, because we are about
to reach the limits of what can fit on a DM42. This release uses 711228 bytes
out of the 716800 (99.2%).

Without the Intel Decimal Library code, we use only 282980 bytes. This means
that the Intel Decimal Library code uses 60.2% of the total code space. Being
able to move further requires a rather radical rethinking of the project, where
we replace the Intel Decimal Library with size-optimized decimal code.

As a result, release 0.6.0 introduces a new table-free and variable-precision
implementation of decimal computations. In this release, most operations are
implemented, but some features are still missing (e.g. Gamma function). This
release will be simultaneous with 0.5.2, which is functionally equivalent but
still uses the Intel Decimal library. The new implementation is much more
compact, allowing us to return to normal optimizations for the DM42 and regain
some of the lost performance. On the other hand, having to switch to a table
free implementation means that it's significantly slower than the Intel Decimal
Library. The upside of course is that you can compute with decimal numbers that
have up to 9999 digits, and a decimal exponent that can be up to 2^60
(1 152 921 504 606 846 976).


### New features

Variable precision decimal floating point implementation for arithmetic,
trigonometrics, logs, exponential and integer factorial. Other functions may
still return "unimplemented error".

### Bug fixes

None. If anything, this release introduces bugs in computations and performance
regressions. However, it frees *a lot* of space for further DM42 development.

### Improvements

The `Precision` setting now sets the number of digits with a granularity of one,
between 3 and 9999. Ideal use of memory is with multiples of 12 digits, e.g. 12,
24 or 36 digits, where decimal packing does not cause lost bits.

Performance on the DM42 is somewhat improved, since it is now possible to return
to a higher level of optimization.

### Regressions

In addition to lower performance and unimplemented functions, this version no
longer builds a compatible QSPI. This means that returning to the DM42 requires
flashing *both* the QSPI and the PGM file.


## Release 0.5.2 "Christmas Eve": Reaching hard limits on the DM42

This release was a bit longer in coming than earlier ones, because we are about
to reach the limits of what can fit on a DM42. This release uses 711228 bytes
out of the 716800 (99.2%).

Without the Intel Decimal Library code, we use only 282980 bytes. This means
that the Intel Decimal Library code uses 60.2% of the total code space. Being
able to move further requires a rather radical rethinking of the project, where
we replace the Intel Decimal Library with size-optimized decimal code.

As a result, release 0.5.2 will be the last one using the Intel Decimal Library,
and is release in parallel with 0.6.0, which switches to a table-free and
variable-precisions implementation of decimal code that uses much less code
space. The two releases should otherwise be functionally identical

### New features

* Shift and rotate instructions (#622)
* Add `CompatibleTypes` and `DetsailedTypes` setting to control `Type` results
* Recognize HP-compatible negative values for flags, e.g. `-64 SF` (#625)
* Add settings to control multiline result and stack display (#634)

### Bug fixes

* Truncate to `WordSize` the small results of binary operations (#624)
* Fix day-of-week shortcut in simulator
* Avoid double-evaluation of immediate commands when there is no help
* Generate an error when selecting base 1 (#628)
* Avoid `Number too big` error on based nunbers
* Correctly garbage-collect menu entries (#630)
* Select default settings that allow solver to find solutions (#627)
* Fix display of decimal numbers (broken by multi-line display)
* Fix rendering of menu entries for `Fix`, `Std`, etc
* Detect non-finite results in arithmetic, e.g. `(-8)^0.3`m (#635, #639)
* Fix range-checking for `Dig` to allow `-1` value
* Accept large values for `Fix`, `Sci` and `Eng` (for variable precision)
* Restore missing last entry in built-in units menu (#638)
* Accept `Hz` and non-primary units as input for `ConvertToUnitPrefix` (#640)
* Fix LEB128 encoding for signed value 64 and similar (#642)
* Do not parse `IfThenElse` as a command
* Do not consider `E` as a digit in decimal numbers (#643)
* Do not parse `min` as a function in units, but as minute (#644)

### Improvements

* Add `OnesComplement` flag for binary operation (not used yet)
* Add `ComplexResults` (-103) flag (not used yet)
* Accept negative values for `B→R` (according to `WordSize`)
* Add documentation for `STO` and `RCL` accessing flash storage
* Mention `True` and `False` in documentation
* Rename `MaxBigNumBits` to `MaxNumberBits`
* Return HP-compatible values from `Type` function
* Minor optimization of flags implementation
* Catalog auto-completion now suggests all possible spellings (#626)
* Add aliases for `CubeRoot` and `Hypothenuse`
* Align based number promotion rules to HP calculators (#629)
* Expand the range of garbage collector integrity check on simulator
* Show command according to preferences in error messages (#633)
* Avoid crash in `debug_printf` if used before font initialization
* Update performance data in documentation
* Add ability to disable any reference to Intel Decimal Floating-point library
* Simplify C++ notations for safe pointers (`+x` and `operartor bool()`)
* Fix link to old `db48x` project in `README.md`


## Release 0.5.1 "Talents": More RPL commands

This release focuses on rounding up various useful RPL commands
and bringing RPL a bit closer to feature-complete.

### New features

* Portable bit pattern generation commands, `gray` and `rgb` (#617)
* Add support for packed bitmaps (#555)
* Implement RPL `case` statement, extended with `case when` (#374)
* `Beep` command (#50)
* `List→` command (#573)
* `Size` command (#588)
* `Str→` command (#590)
* `Obj→` command (#596)
* Add flag to control if `0^0` returns `1` or undefined behaviour (#598)
* Unicode-based `Num` and `Chr` commands, `Text→Code` and `Code→Text` (#597)
* `IP` and `FP` commands (#601)
* Percentage operations `%`, `%CH` and `%T` (#602)
* `Min` and `Max` operations (#603)
* `Floor` and `Ceil` operations (#605)
* `Get` with a name argument (#609)
* `Put` command (#610)
* `Head` and `Tail` commands (#614)
* `Map`, `Reduce` and `Filter` commands (#613)

### Bug fixes

* Ensure rounded rectangles stay within their boundaries (#618)
* Prevent auto-power-off for long-running programs (#587)
* Fix old-style RPL shortcuts for `FS?C` and the like
* Add `FF` shortcut for `FlipFlag`
* Fix rendering of `<`, `>`, etc in old-style RPL compatibility mode (#595)
* Update various menus
* Evaluate program arguments in `IFT` and `IFTE` (#592)
* Evaluate algebraic expressions in `if`, `while` and `case` (#593)
* Load variables from state file in correct order (#591)
* Avoid truncation of state file when ASCII conversions occur (#589)
* Clear debugging state more completely after `kill` (#600)
* `Wait` no longer makes it harder to stop a program (#619)
* `mod` no longer gives wrong result for negative fractions and bignums (#606)
* No longer strip tags in non-numeric arithmetic operations (#607)

### Improvements

* Small updates to demo file
* A long `Wait` command allows the calculator to switch off (#620)
* Centering of variable names in `VariablesMenu` (#610)
* Makefile `check-ids` target to check if commands are in help or menus (#615)


## Release 0.5.0: Statistics and flags

This release provides statistics functions and flags.

### New features

* Statistics (#495) and linear regression (#569)
* File-based statistics (#571)
* `Sort`, `QuickSort`, `ReverseSort`, `ReverseQuickSort` and `RevList` (#572)
* Flags, i.e. `CF`, `SF`, `FS?`, etc (#43)
* Plot scaling commands such as `SCALE`, `CENTR`, `XRNG`, ... (#582)
* Add `CurveFilling` and `DrawPlotAxes` setting flags (#580)
* `ScatterPlot` (#577) and `BarPlot` (#579)

### Bugs

* Save settings enumerations as portable text (#565)
* Avoid infinite loop when reading at end of help file
* Repair behaviour of `-1 DIG`, broken by settings improvements
* Fix definition of `rpm` in units and units file
* Crash in `list::map` when called function errors out (#570)
* Fix editor horizontal movement when inserting commands (#576)
* Repair plotting demo (#583)
* Fix vertical position of axes in `DrawAxes` (#584)
* Very long drawing loop if `ppar` axes are backwards (#585)

### Improvements

* Sets editor selection correctly for command-line errors
* Ability to parse command and setting names in quotes, e.g. `'Radians'`
* Insert command names inside quotes (#575)
* Update documentation of implemented features (#569)
* Make `PlotParameters` a keyword (#578)

## Release v0.4.12: Emergency bug fixes, filesyste, access

A few quick bug fixes related to issues found in 0.4.11.

### New features

* `STO` and `RCL` to file (#375)
* Parsing of text containing quotes (#562)

### Improvements

* Rework file load/save dialog boxes
* Preliminary plumbing for statistics functions

### Bugs

* Error loading state files that contain directories (#559)
* Font setting for result was taken from editor font (#560)
* Crash running the `Shapes` demo (#563)

## Release 0.4.11: Debugging, Units, Settings

This release implements debugging, infinite RPL recursion, mixed
fractions, customizable units cycling, and restores missing entries in
the units menu.

### New features

* Allow customization of `Cycle` for units (#534)
* Allow infinite recursion in RPL code (#537)
* RPL program and expression debugging (#552) including after EXIT
* Mixed fractions such as `1 1/3` (#554)
* `BeepOn` and `SilentBeepOn` features (#280)
* `ScreenCapture` and keyboard shortcut (#434)

### Bugs

* Accept `2.3 FIX` and `#0 Background` (#557)
* Do not parse `67.200525` as a `decimal32` (#551)
* Bump low battery voltage to 2.550V (#553)

### Improvements

* Catalog shows all commands *containing* typed text (#556)
* Reorganize the units menu (#550) and restore missing units
* Remember menu page for `LastMenu` (#545)
* `SPC` key inserts `;` when inside parenthese (#499)
* Settings are now entirely defined by `ids.tbl` (#294)
* Improve user interface code consistency
* Improve GC handling of "just-past-end-of-object" pointers
* Remove the `execute()` RPL callback, rely on `evaluate()`
* Optimize allocation of 1-byte vs 2-byte opcodes
* Render `abs` as `abs` and not `norm` (accept `norm` while parsing)

## Release v0.4.10: Performance and units file

This release focuses on display performance optimization and support
for unit data files.

### New features

* Cycle command for units (#517)
* Possibility to load units from config/units.csv file (#496, #544)
* Internal: debug_printf facility (#541)
* ShowBuiltinUnits and HideBuiltinUnits settings (#542)
* Provide config/units.csv example file (#543)
* Build units menu from units file (#544)

### Bugs

* Possible memory corruption in expressions
* Calculator lock-up trying with unit conversions in numeric mode (#529)
* Numerator and divisor no longer truncated to 32-bit (#539)
* Correctly save LastArg for interactive operations (#540)

### Improvements

* Optimize the font cache, makes stack drawing faster in SCI mode (#526)
* Add TypeName to object menu (#527)
* Regroup units in units menu by scale (#528)
* Status of implementation and performance data in documentation (#530)
* Performance: Reduce frequency of busy cursor drawing (#531)
* Performance: Reimplement range-based type checkig (#532)
* Performance: Focused -O3 optimizations on DM42 (#533)
* Makefile: Install target installs demo and config (#547)
* Garbage collector for menu labels (#548)


## Release 0.4.9 - Support for units

This release focuses on support for units, but also adds a large number of other
fixes and improvements.

### New features

* Power-off message indicating low-battery situation (#521)
* Add ConvertToUnixPrefix command and SI prefix menu keys (#513)
* Recognize all units that exist in the HP48, and a few more (#491)
* UFACT (FactorUnit) command (#512)
* Unit simplification, e.g. turn 1_m^2*s/s/m into 1_m (#506)
* Converting unity units to numbers (#502)
* →Unit command (#501)
* UnitValue (UVAL) command (#493)
* Implement "kibibytes" (KiB) and power-of-two SI prefixes (#492)
* Unit arithmetic (#481)
* Add B->R and R->B to BasesMenu (#488)
* Implement term reordering capability in rewrite (#484)
* BaseUnits (UBase) command (#483)
* Unit parsing for complex units, e.g. 1_cm^2 (#482)
* Unit arithmetic (#481) including automatic conversions (#480)
* Convert command (#480)
* Implement the Cycle command for unit objects
* Add Å character for angstroem (#477)
* Add Merge state to State system menu (#475)
* Use Unicode font to display the name of a program when executing it (#469)
* Allow incremental search to find digits and Unicode (#468)
* Add tool glyph to user interface font

### Bug fixes

* Do not parse symbols beyond input buffer (#524)
* Parse unit menu entries as expressions, not symbols (#523)
* Fix reduced-precision arithmetic (#521)
* Do not parse empty denominator as zero, e.g. 2/s (#520)
* Do not parse a fraction inside a power, e.g. X^2/3 (#519)
* Convert fractions to decimal in numeric mode (#516)
* Do not emit mantissa_error for valid numbers (#515)
* Apply negation correctly on unit objects (#500)
* Do not emit separator after trailing 0 in integer decimals (#489)
* Do not emit extra spacing before decimal separator (#485)
* Fix stack depth in one error case of evaluate_function()
* Fix display of next/previous icons for large menus (#478)
* Clear settings when loading a state (#474)
* Fix separators in whole part of decimal numbers when setting is not 3 (#464)
* Parse (sin x)²+(cos x)² correctly, as well as HP67 Mach example (#427)

### Improvements

* Rename equation as expression (#518) and labelText as label_text
* Do not update LastArg except for command line (#511)
* ToolsMenu: Connect units to the UnitsConversionMenu (#514)
* Display unit using / and ·, e.g. 1_m·s^2/A (#507)
* Show units menu for inverse units as mm⁻¹ (#503)
* Display battery level more accurately, i.e. consider 2.6V "low" (#476)
* No longer acccept empty equations or parentheses, e.g. 1+() (#487)
* Make StandardDisplay mode obey MinimumSignificantDigits (#462)
* Add algebraic evaluation function for easier evaluation in C++ code
* Reimplement unit type as a derivative of complex (#471)
* documentation: Use 🟨 and 🟦 for more commands (#467)
* Swap Search and Copy commands in EditorMenu (#466)
* STO stores variables at beginning of directory (#462)
* documentation: Add quickstart guide, used for video recording
* documentation: Add links to YouTube videos
* documentation: Add release notes
* documentation: Some typos and other improvements
* documentation: Rework section on keyboard mappings
