# Simulácia výroby tepelnej energie za pomoci fotovoltaických panelov a tepelného čerpadla

Školský projekt VUT FIT Brno tretí ročník bakalárskeho štúdia pre predmet Modelovani a simulace (IMS).

## O programe

Program simuluje produkciu energie pomocou fotovoltaických panelov, ktorá sa použije na vykurovanie rôzne veľkých priestorov. Program si vypočíta približný objem vyrobenej energie pomocou fotovoltaických panelov, a z tejto energie každý deň prebehne úbytok s náhodnými odchýlkami získanými pomocou štúdie spotreby energie na vykurovanie.

## Použitie

```bash
make 
```

```bash
./run [-h || --help] [-p || --panels] [-pp || --panelProduction] [-a || --areaSize] [-hc || --heatConsumption] [-ch || --monthChoice] [-hpc || --heatPumpConsumption number]
```

### Parametry

- `-h || -- help`
  - Voliteľný parameter **-h || --help** poskytne napovedu k programu
- `-p || -- panels`
  - Voliteľný parameter **-p || --panels** definuje pocet panelov
- `-pp || panelProduction`
  - Voliteľný parameter **-pp || --panelProduction** urcuje produkciu solarneho panelu za rok
- `-a || --areaSize`
  - Voliteľný parameter **-a || --areaSize** definuje rozlohu objektu
- `-hc || --heatConsumption`
  - Voliteľný parameter **-hc || --heatConsumption** určuje rocnu priemernu spotrebu elektickej energie na vykurovanie
- `-ch || --monthChoice`
  - Voliteľný parameter **-ch || --monthChoice** určuje pre ktorý mesiac má prebehnúť simulácia <1 - 12>, v prípade nezadania parametru si program automaticky vyberie náhodny mesiac
- `-hpc || --heatPumpConsumption`
  - Voliteľný parameter **-hpc || --heatPumpConsumption** určuje optimalny vykon tepelneho cerpadla

Každý z voliteľných parametrov (okrem --help) je následovaný číslom.

## Autori

Adam Dzurilla xdzuri00  
Martin Mores xmores02