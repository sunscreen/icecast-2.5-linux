#ifdef HAVE_FLAC
extern "C" {
FLAC__StreamEncoderWriteStatus FLACWriteCallback(
									const FLAC__StreamEncoder	*encoder,
									const FLAC__byte				buffer[],
									unsigned						bytes,
									unsigned						samples,
									unsigned						current_frame,
									void							*client_data
								) {
	altacastGlobals	*g = (altacastGlobals *) client_data;

	int sentbytes = sendToServer(g, g->gSCSocket, (char_t *) buffer, bytes, CODEC_TYPE);

	if(sentbytes < 0) {
		g->flacFailure = 1;
		disconnectFromServer(g); /* with love from icytwozero */
		return FLAC__STREAM_ENCODER_WRITE_STATUS_FATAL_ERROR; /* with love from icytwozero */
	}
	else {
		g->flacFailure = 0;
		
	}

	return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
}
}
extern "C" {
void FLACMetadataCallback(const FLAC__StreamEncoder	*encoder,
													const FLAC__StreamMetadata *metadata, 
													void *client_data) {
	altacastGlobals	*g = (altacastGlobals *) client_data;

	return;
}
}
#endif
