package com.iryaniv.jbpf;

class JBpf {
    private native int validate(String filter, byte[] packet);

    public boolean checkBpf(String filter, byte[] packet) {
        return (validate(filter, packet) == 1);
    }

    static {
        System.loadLibrary("Bpf");
    }
}

