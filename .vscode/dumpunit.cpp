/*
 * File: dumpunit.cpp
 *
 * logue sdk user unit SysEx dump payload extractor
 * 
 * 2021 (c) Oleg Burdaev
 * mailto: dukesrg@gmail.com
 *
 */

#include <stdio.h>
#include <sys/stat.h>
#include "userprg.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <logue unit sysex dump file>\n", argv[0]);
		return 1;
	};

	FILE *fp = fopen(argv[1], "rb");
	unsigned char data[65536];
        char name[USER_PRG_NAME_LEN+1+14];
	user_prg_header_t *header = (user_prg_header_t *)&data[8];
	unsigned int *id = (unsigned int *)&data[0];
	unsigned int i, j = 0;
	unsigned char h, l = 0;

	fread(&data, 1, 10, fp);
	if (id[0] != 0x003042F0 || (id[1] & 0x00FF00FF) != 0x004A0001 || data[9] == 0xF7) {
		printf("No logue unit dump detected!\n", argv[0]);
		fclose(fp);
		return 1;
	}

	while (fread(&h, sizeof h, 1, fp) > 0) {
		for (i = 0; i < 7 && fread(&l, sizeof l, 1, fp) > 0; i++)
			data[j++] = l | ((h & (1 << i)) ? 0x80 : 0);
	}
	fclose(fp);

	mkdir(header->name, 0777);

        sprintf(name, "%s/manifest.json", header->name);
	fp = fopen(name, "w");
	fprintf(fp, "{\n");
	fprintf(fp, "    \"header\" :\n");
	fprintf(fp, "    {\n");
	fprintf(fp, "        \"platform\" : \"");
	switch(header->target & USER_TARGET_PLATFORM_MASK) {
		case k_user_target_prologue:
			fprintf(fp, "prologue");
			break;
		case k_user_target_miniloguexd:
			fprintf(fp, "minilogue-xd");
			break;
		case k_user_target_nutektdigital:
			fprintf(fp, "nutekt-digital");
			break;
	}
	fprintf(fp, "\",\n");
	fprintf(fp, "        \"module\" : \"");
	switch(header->target & USER_TARGET_MODULE_MASK) {
		case k_user_module_modfx:
			fprintf(fp, "modfx");
			break;
		case k_user_module_delfx:
			fprintf(fp, "delfx");
			break;
		case k_user_module_revfx:
			fprintf(fp, "revfx");
			break;
		case k_user_module_osc:
			fprintf(fp, "osc");
			break;
	}
	printf("%s/%s\n%s/%s\n", header->name, "manifest.json", header->name, "payload.bin");
	fprintf(fp, "\",\n");
	fprintf(fp, "        \"api\" : \"%d.%d-%d\",\n", USER_API_MAJOR(header->api), USER_API_MINOR(header->api), USER_API_PATCH(header->api));
	fprintf(fp, "        \"dev_id\" : %u,\n", header->dev_id);
	fprintf(fp, "        \"prg_id\" : %u,\n", header->prg_id);
	fprintf(fp, "        \"version\" : \"%d.%d-%d\",\n", USER_API_MAJOR(header->version), USER_API_MINOR(header->version), USER_API_PATCH(header->version));
	fprintf(fp, "        \"name\" : \"%s\",\n", header->name);
	fprintf(fp, "        \"num_param\" : %d,\n", header->num_param);
	fprintf(fp, "        \"params\" : [\n");
	for (i = 0; i < header->num_param; i++)
		fprintf(fp, "            [\"%s\", %d, %d, \"%s\"]%s\n", header->params[i].name, header->params[i].min, header->params[i].max, header->params[i].type == k_user_prg_param_type_select ? "" : "%", i < (header->num_param - 1) ? "," : "");
	fprintf(fp, "        ]\n");
	fprintf(fp, "    }\n");
	fprintf(fp, "}\n");
	fclose(fp);

        sprintf(name, "%s/payload.bin", header->name);
	fp = fopen(name, "wb");
	for (i = sizeof(user_prg_header_t) + 8; i < sizeof(user_prg_header_t) + 8 + header->load_size; i++)
		fwrite(&data[i], 1, 1, fp);
	fclose(fp);
}
