EXE=../shape_Handler

inputList=$(ls testFile/*.in)
outputList=$(ls testFile/*.out)

NumberOfInput=$( echo $inputList | wc -w)

for i in `seq 1 $NumberOfInput`
do
	INPUT=$( echo $inputList | awk "{ print \$$i }")
	REF_OUTPUT=$( echo $outputList | awk "{ print \$$i }")
	OUTPUT=testFile/output/out$i

	echo ""
	echo "=============================================================================="
	echo "Éxecution de $INPUT"
	echo "=============================================================================="
	echo ""

	/usr/bin/time -v $EXE < $INPUT > $OUTPUT

	echo "---"
	echo "Fichier de sortie écrit dans: $OUTPUT"
	echo "Diférences trouvées avec la sortie attendu:"
	echo ""

	diff $OUTPUT $REF_OUTPUT --report-identical-files --side-by-side --suppress-common-lines
done
