# MiniBot

MiniBot ist ein Arduino-gesteuerter Modellbauroboter

# Serielle Schnittstelle

Commands werden über "Messages" seriell an den Roboter Übertragen.

Serielle Messages haben als 1. Charakter den typ (z.B: 'T')

Serielle Messages enden mit '\n'

## Commands

### Allgemein

* Modus Wechseln:
    * Automatik
    * Manuell
    * Aus

### Automatik

* Programm senden:
    Programm kann nur gesendet werden, während der Ablauf gestoppt ist

* Ablauf kontrollieren:
    * Ablauf Starten: Start (S)
    * Ablauf Pausieren: Pause (P)
    * Ablauf Stoppen: Break(B)

### Manuell

* Befehl senden

## Table

| Index | CHAR | Benennung            | Data        |
|-------|------|----------------------|-------------|
| 00    | M    | Modus Wechseln       | char: A/M/O |
| 10    | P    | Programm senden      | programm    |
| 11    | C    | Ablauf kontrollieren | char: S/P/B |
| 20    | B    | Befehl senden        | befehl      |

# Daten

## Befehl

```
MOVE_TYPE;SPEED;X;Y;Z;ANGLE;
```

## Programm

```
SIZE|BEFEHL|BEFEHL|...|
```
