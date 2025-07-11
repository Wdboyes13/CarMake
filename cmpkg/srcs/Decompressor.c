#include "Common.h"

#define CHUNK_SIZE 16384

int DecompressZst(const char* in_path, const char* out_path) {
    FILE *fin = fopen(in_path, "rb");
    if (!fin) return perror("Failed to open input"), 1;

    FILE *fout = fopen(out_path, "wb");
    if (!fout) return perror("Failed to open output"), 2;

    void* in_buf = malloc(CHUNK_SIZE);
    void* out_buf = malloc(CHUNK_SIZE);
    if (!in_buf || !out_buf) return perror("Memory allocation failed"), 3;

    ZSTD_DCtx* dctx = ZSTD_createDCtx();
    if (!dctx) return perror("ZSTD context failed"), 4;

    size_t ret;
    while ((ret = fread(in_buf, 1, CHUNK_SIZE, fin)) > 0) {
        ZSTD_inBuffer input = { in_buf, ret, 0 };
        while (input.pos < input.size) {
            ZSTD_outBuffer output = { out_buf, CHUNK_SIZE, 0 };
            size_t res = ZSTD_decompressStream(dctx, &output, &input);
            if (ZSTD_isError(res)) {
                fprintf(stderr, "Decompression error: %s\n", ZSTD_getErrorName(res));
                return 5;
            }
            fwrite(out_buf, 1, output.pos, fout);
        }
    }

    ZSTD_freeDCtx(dctx);
    free(in_buf);
    free(out_buf);
    fclose(fin);
    fclose(fout);
    return 0;
}