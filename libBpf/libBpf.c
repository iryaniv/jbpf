#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <jni.h>
#include <libBpf.h>

typedef unsigned int uint_t;
typedef int bool_t;

JNIEXPORT jint JNICALL Java_BpfJava_validate(JNIEnv *env, jobject obj, jstring jbpfString, jbyteArray jPacketBuffer) {
     struct timeval ts;
     gettimeofday(&ts, NULL);
     struct pcap_pkthdr hdr = {.ts = ts, .caplen=82, .len=82 };
     const char* bpfString = (*env)->GetStringUTFChars(env, jbpfString, 0);
     unsigned char* packetData = (unsigned char*)(*env)->GetByteArrayElements(env, jPacketBuffer, NULL);
     int r = is_packet_valid_by_filter(bpfString, hdr, packetData);
     (*env)->ReleaseStringUTFChars(env, jbpfString, bpfString);
     return r;
}

bool_t print_error_and_die(char *s) {
	fprintf(stderr, "%s", s);
	exit(-1);
}

static struct bpf_program g_fp;

void init_filter(char* filter) {
	pcap_t *handle;
	handle = pcap_open_dead(DLT_EN10MB, 65536);
	if (!handle) {
		print_error_and_die("pcap_open_offline_failed");
	}
	if(pcap_compile(handle, &g_fp, filter, 1, -1) == -1) {
		print_error_and_die("pcap_compile failed");
	}
}

int is_packet_valid_by_filter(char* filter, struct pcap_pkthdr *hdr, unsigned char *pkt) { 
	init_filter(filter);
	if (pcap_offline_filter(&g_fp, hdr, pkt)) {
		return 1;
	}
	return 0;
}