alias Membrane.Demo.VideoPipeline
{:ok, pid} = VideoPipeline.start_link("https://membraneframework.github.io/static/video-samples/test-video.h264")
VideoPipeline.play(pid)
