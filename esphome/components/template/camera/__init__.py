from esphome.components import camera

CONFIG_SCHEMA = camera.camera_schema()


async def to_code(config):
    await camera.new_camera(config)
