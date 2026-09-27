# CampusGuard

COS 214 Practical 5 — an emergency-response coordination platform for a university
campus. CampusGuard reports incidents, dispatches security/medical/facilities response
units, restricts or restores access to affected campus areas, and issues alerts, all
coordinated through a small set of collaborating services rather than one another
directly.

## Team

| Name | Student Number |
|---|---|
| Simon Vogel | u25087984 |
| _TODO_ | _TODO_ |
| _TODO_ | _TODO_ |

## Running the application (Docker — used for the demonstration)

The assessed demonstration is launched with Docker Compose. From the project root:

```bash
docker compose up --build
```

This builds an `ubuntu:24.04` image, installs `g++`, `make`, `gdb` and `valgrind`,
compiles the project with `make`, and runs `./campusguard`.

To rebuild from a clean state:

```bash
docker compose up --build --force-recreate
```

To stop:

```bash
docker compose down
```

## Running locally without Docker

Requires `g++` (C++11) and GNU Make.

```bash
make          # build the campusguard executable
make run      # build (if needed) and run it
make clean    # remove object files and the executable
```

### Debugging and memory-checking locally

```bash
make gdb        # build (if needed) and open the executable in gdb
make valgrind   # build (if needed) and run under valgrind (full leak check)
```

The same commands work inside the Docker container, e.g.:

```bash
docker compose run campusguard make valgrind
docker compose run campusguard make gdb
```

## Design patterns

CampusGuard makes meaningful use of six GoF patterns:

- **Command** — `Command` (abstract) with `HandleIncidentCommand`, `DispatchUnitCommand`,
  `SendAlertCommand`, `RestrictAccessCommand` and `RestoreAccessCommand` as concrete
  commands, invoked and tracked (with undo) by `OperatorConsole`.
- **Mediator** — `Coordinator` / `CampusCoordinator` lets `Service` colleagues
  (security, medical, facilities, alerts, access control) react to one another's
  reports without depending on each other directly.
- **Adapter** — `AccessControlAdapter` adapts the incompatible `LegacyAccessControlSystem`
  interface (`activateLock`/`deactivateLock`) to the `AccessControlService` interface
  (`restrictAccess`/`restoreAccess`) CampusGuard expects.
- **Facade** — `EmergencyDesk` gives a simple entry point (e.g. `respondToFire`,
  `handleIncident`) over the coordinator, console, and all five services.
- **State** — `IncidentStatus` (Reported/Active/Resolved/Cancelled) and `UnitStatus`
  (Available/Dispatched/Operating/Unavailable) drive behaviour based on current state.
- **Composite** — `CampusComponent`/`CampusZone`/`CampusUnit` model the campus as a
  tree, traversed at runtime (e.g. `LegacyAccessControlSystem` looks components up
  by code through the composite tree).

## Project layout

All sources are flat in the project root (see the `Makefile`, which compiles every
`.cpp` file present). Entry point: `Main.cpp`.