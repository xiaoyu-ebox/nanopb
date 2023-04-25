#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "pb_decode.h"
#include "pb_encode.h"
#include "proto/watchface.pb.h"

// python ..\..\..\nanopb\generator\nanopb_generator.py .\proto\watchface.proto
// python ..\..\..\nanopb\generator\nanopb_generator.py -L '#include ""%s""' .\proto\watchface.proto
// python ..\..\..\nanopb\generator\protoc .\proto\watchface.proto --python_out=. demo.proto
int main(int argc, char **argv)
{
    uint8_t enc_buf[512] = {0};

    // 组包
    wf_obj wf_obj_test[2];
    wf_obj_list wf_obj_enc = wf_obj_list_init_zero;

    wf_obj_test[0].which_obj = wf_obj_img_tag;
    wf_obj_test[0].img.value = 1;
    strcpy(wf_obj_test[0].img.text, "hello world");

    wf_obj_test[1].which_obj = wf_obj_label_tag;
    wf_obj_test[1].label.value = 0x2345;

    wf_obj_enc.obj_count = 1;
    wf_obj_enc.obj = wf_obj_test;
    pb_ostream_t o_stream = pb_ostream_from_buffer(enc_buf, sizeof(enc_buf));
    bool ret = pb_encode(&o_stream, wf_obj_list_fields, &wf_obj_enc);
    printf("encode ret = %s, size:%u\n", PB_GET_ERROR(&o_stream), o_stream.bytes_written);


    // 解包
    wf_obj_list wf_obj_dec = wf_obj_list_init_zero;
    pb_istream_t i_stream = pb_istream_from_buffer(enc_buf, o_stream.bytes_written);

    ret = pb_decode(&i_stream, wf_obj_list_fields, &wf_obj_dec);
    if(!ret)
        printf("decode ret = %s\n", PB_GET_ERROR(&i_stream));
    printf("obj_count = %d\n", wf_obj_dec.obj_count);
    printf("obj = %p\n", wf_obj_dec.obj);
    if(wf_obj_dec.obj) {
        printf("obj.type = %u - %u\n", wf_obj_dec.obj[0].which_obj, wf_obj_dec.obj[1].which_obj);

        if(wf_obj_dec.obj[0].which_obj == wf_obj_img_tag) {
            printf("img.value = %x\n", wf_obj_dec.obj[0].img.value);
            printf("img.text = %s\n", wf_obj_dec.obj[0].img.text);
        }

        if(wf_obj_dec.obj[1].which_obj == wf_obj_label_tag) {
            printf("label.value = %x\n", wf_obj_dec.obj[1].label.value);
        }
    }
    pb_release(wf_obj_list_fields, &wf_obj_dec);

    return 0;
}