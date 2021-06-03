# Cockpit de simulateur de vol

* `master` est l'interface avec le PC (arduino micro pro)
* `sensors` est le gestionnaire de capteur (arduino nano)

Les deux arduinos sont connectés en i2c

## Les capteurs

* Les switchs sont connectés de `D3` à `D9`
* La profondeur utilise un H9757 (capteur optique) connecté sur `D2` (detecteion de seuil) et `D10` (detection de direction)
* Le roulis est connecté en `A7`
* La réchauf carbu est connecté en `A0`
* La manette des gaz est connecté en `A1`
* Le pas de l'hélice est connecté en `A2`
* La richesse est connecté en `A3`
* Le trim de profondeur est connecté en `A6`

