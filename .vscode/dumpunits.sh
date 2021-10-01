#!/bin/bash
declare -A DEVICEIDS=(["prologue"]="73" ["minilogue xd"]="81" ["NTS-1 digital kit"]="87")
declare -A EXTENSIONS=(["73"]="prlgunit" ["81"]="mnlgxdunit" ["87"]="ntkdigunit")
declare -A MAXSLOTS=(["modfx"]="15" ["delfx"]="7" ["revfx"]="7" ["osc"]="15")
declare -A UNITINDEX=(["modfx"]="1" ["delfx"]="2" ["revfx"]="3" ["osc"]="4")
declare -A UNITNAMES=(["modfx"]="Modulation FX" ["delfx"]="Delay FX" ["revfx"]="Reverb FX" ["osc"]="Oscillator")
SENDPORT=$(sendmidi list | grep -E "(prologue|minilogue xd|NTS-1 digital kit) SOUND" | head -n1)
RECEIVEPORT=$(receivemidi list | grep -E "(prologue|minilogue xd|NTS-1 digital kit) KBD/KNOB" | head -n1)
([ -z "$SENDPORT" ] || [ -z "$RECEIVEPORT" ]) && echo $PORTNAME Synthesizer is not connected && exit 1
DEVICEID=${DEVICEIDS[${SENDPORT% SOUND}]}
[ -f ".vscode/dumpunit" ] || gcc .vscode/dumpunit.cpp -o.vscode/dumpunit -Ilogue-sdk/platform/inc 
echo -e "Dumping ${SENDPORT% SOUND} units...\n"
for UNITTYPE in modfx delfx revfx osc; do
    INDEX=0
    while [[ $INDEX -le ${MAXSLOTS[$UNITTYPE]} ]] ; do
        echo -n "${UNITNAMES[$UNITTYPE]} ${INDEX}: "
        receivemidi dev "$RECEIVEPORT" syx | sed -E "s/system-exclusive hex (.*) dec/F0 \1 F7/" | xxd -r -p > ${UNITTYPE}${INDEX}.syx &
        sendmidi dev "$SENDPORT" syx 66 48 0 1 $DEVICEID 26 ${UNITINDEX[$UNITTYPE]} $INDEX
        sleep 2
        kill $(ps | awk '/receivemidi/{print $1}')
        NAME=$(.vscode/dumpunit ${UNITTYPE}${INDEX}.syx | head -n1 | cut -d/ -f1)
         ([ -d "$NAME" ] && echo -n "\"${NAME}\" " && mv ${UNITTYPE}${INDEX}.syx "$NAME-$UNITTYPE.syx" && echo -n "$NAME-$UNITTYPE.syx " && zip -r -m -q "$NAME-$UNITTYPE.${EXTENSIONS[$DEVICEID]}" "$NAME" && echo $NAME-$UNITTYPE.${EXTENSIONS[$DEVICEID]}) || (rm -f ${UNITTYPE}${INDEX}.syx && echo free.)
        (( INDEX += 1 ))
    done    
    echo
done
