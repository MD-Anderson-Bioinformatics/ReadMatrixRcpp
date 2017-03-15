

getZipDir <- function()
{
  zipFile <- Sys.getenv("GS_ZIP_ARCHIVE")
  if(!file.exists(zipFile))
  {
    zipFile <- "/temp/GeneSurvey.zip"
    if(!file.exists(zipFile))
    {
      zipFile <- "/geneSurveyData/TESTING/GeneSurvey.zip"
      if(!file.exists(zipFile))
      {
        zipFile <- NULL
      }
    }
  }
  zipFile
}
