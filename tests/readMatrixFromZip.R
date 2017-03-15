library(ReadMatrixRcpp)

#################################################################
#################################################################

zipFile <- getZipDir()
if (!is.null(zipFile))
{
  matrixFile <- "combined/illuminahiseq_mirnaseq_isoform/platform.tsv"
  matrix <- readMatrixFromZip(zipFile, matrixFile)
  mysize <- dim(matrix)
  (980==mysize[1])&&(9695==mysize[2])
} else {
  message("No test data. Skip test.")
  TRUE
}
