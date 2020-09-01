#include "host_capture_command.hpp"

HostCaptureCommand::HostCaptureCommand(const StreamInfo& streamToSendCommand) : stream(streamToSendCommand){ /* empty body */ }

void HostCaptureCommand::sendCaptureMetadata(CaptureMetadata meta){
    StreamData captureMetadata;
    captureMetadata.packet_number = 0;
    captureMetadata.data = &meta;
    captureMetadata.size = sizeof(CaptureMetadata);
    notifyObservers(stream, captureMetadata);
}

void HostCaptureCommand::sendDisparityConfidenceThreshold(uint8_t confidence_thr){
    StreamData conf_thr_metadata;
    conf_thr_metadata.packet_number = 0;
    conf_thr_metadata.data = &confidence_thr;
    conf_thr_metadata.size = sizeof(confidence_thr);
    notifyObservers(stream, conf_thr_metadata);
}

void HostCaptureCommand::sendCustomDeviceResetRequest(void){
    StreamData custom_reset;
    uint32_t reset = 0xDEADDEAD;
    custom_reset.packet_number = 0;
    custom_reset.data = &reset;
    custom_reset.size = sizeof(reset);
    notifyObservers(stream, custom_reset);
}

void HostCaptureCommand::sendIsp3A(int camera_id, int command_id, const char *extra_args) {
    StreamData cmd_data;
    char cmdfull[256];
    snprintf(cmdfull, sizeof cmdfull, "3A %d %d %s", command_id, camera_id, extra_args);
    cmd_data.packet_number = 0;
    cmd_data.data = cmdfull;
    cmd_data.size = strlen(cmdfull) + 1;
    notifyObservers(stream, cmd_data);
}

void HostCaptureCommand::capture(){
    sendCaptureMetadata(CaptureMetadata::createStillCapture());
}


void HostCaptureCommand::afMode(CaptureMetadata::AutofocusMode mode){
    sendCaptureMetadata(CaptureMetadata::createAfMode(mode));
}

void HostCaptureCommand::afTrigger(){
    sendCaptureMetadata(CaptureMetadata::createAfTrigger());
}
