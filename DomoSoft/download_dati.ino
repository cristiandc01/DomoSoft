void SD_file_download(String filename, String nome) {
  File download = SPIFFS.open(filename, "r");
  if (download) {
    server.sendHeader("Content-Type", "text/text");
    server.sendHeader("Content-Disposition", "attachment; filename=" + nome + ".txt");
    server.sendHeader("Connection", "close");
    server.streamFile(download, "application/octet-stream");
    download.close();
  } 
}
