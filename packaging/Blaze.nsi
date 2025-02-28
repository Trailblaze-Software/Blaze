
!define COMPONENT_NAME "Blaze3D-${VERSION}.las"

Function install_file_associations
    WriteRegStr HKCR ".las" "" "${COMPONENT_NAME}"
    WriteRegStr HKCR ".laz" "" "${COMPONENT_NAME}"

    WriteRegStr HKCR "${COMPONENT_NAME}" "" "LIDAR Point Cloud"
    WriteRegStr HKCR "${COMPONENT_NAME}\DefaultIcon" "" "$INSTDIR\bin\Blaze3D.exe,0"
    WriteRegStr HKCR "${COMPONENT_NAME}\shell\open" "" "Open with Blaze3D-${VERSION}"
    WriteRegStr HKCR "${COMPONENT_NAME}\shell\open\command" "" '"$INSTDIR\bin\Blaze3D.exe" "%1"'

    System::Call 'shell32::SHChangeNotify(i 0x08000000, i 0x1000, i 0, i 0)'
FunctionEnd

Function un.install_file_associations
    DeleteRegKey HKCR "${COMPONENT_NAME}"
FunctionEnd

Section "Associate las/laz files" file_extensions
   Call install_file_associations
SectionEnd

!macro Remove_${file_extensions}
   Call un.install_file_associations
!macroend
