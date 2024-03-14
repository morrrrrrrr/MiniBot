# MiniBot

MiniBot ist ein Arduino-gesteuerter Modellbauroboter

# Backend-API

## EndPoints

**Allgemein**:
* Modus Wechseln
* Grundstellung fahren

* Abfragungen:
    * Modus
    * Zielposition

**Manuell**:
* Input setzen
* Geschwindigkeit setzen
* Ziel anfahren

**Automatik**:
* Programm senden
* Programm starten
* Programm pausieren

* Abfragungen:
    * Aktueller Befehl mit Fortschritt

### Table

| Index | Name               | Endpoint             | GET                          | POST                         | Modus       |
|-------|--------------------|----------------------|------------------------------|------------------------------|-------------|
|     0 | Modus Wechseln     | /api/mode/set        | /                            | (0 - OFF, 1 - AUTO, 2 - MAN) | Allgemein   |
|     1 | Modus Abfragen     | /api/mode/get        | (0 - OFF, 1 - AUTO, 2 - MAN) | /                            | Allgemein   |
|     2 | Ziel Abfragen      | /api/target/get      | json: x, y, z, angle         | /                            | Allgemein   |
|     3 | Input Setzen       | /api/input/pos/set   | /                            | json: x, y, z, angle         | Manuell     |
|     4 | Geschw. Setzen     | /api/input/speed/set | /                            | number: speed in mm/s        | Manuell     |
|     5 | Programm Senden    | /api/prog/send       | /                            | text: program structure      | Automatisch |
|     6 | Programm Starten   | /api/prog/start      | /                            | /                            | Automatisch |
|     7 | Programm Stoppen   | /api/prog/stop       | /                            | /                            | Automatisch |
|     8 | Programm Pausieren | /api/prog/pause      | /                            | /                            | Automatisch |
|     9 | Aktueller Befehl   | /api/prog/command    | json: command structure      | /                            | Automatisch |
