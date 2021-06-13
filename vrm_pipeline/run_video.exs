alias Membrane.Demo.VideoPipeline
{:ok, pid} = VideoPipeline.start_link("sample.mp3")
VideoPipeline.play(pid)
