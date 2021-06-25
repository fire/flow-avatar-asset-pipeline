alias Membrane.Demo.VideoPipeline
{:ok, pid} = VideoPipeline.start_link()
VideoPipeline.play(pid)
