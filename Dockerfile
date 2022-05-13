FROM qmkfm/qmk_cli

VOLUME /qmk_firmware
WORKDIR /qmk_firmware

ENTRYPOINT qmk
CMD compile -kb all -km default
