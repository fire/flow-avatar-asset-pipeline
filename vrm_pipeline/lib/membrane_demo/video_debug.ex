defmodule Membrane.Demo.VideoDebug.Sink.Buffers do
  @moduledoc """
  Fake sink that ignores coming data. It makes demands in buffers.
  """

  use Membrane.Sink

  def_input_pad :input, demand_unit: :buffers, caps: :any

  @impl true
  def handle_prepared_to_playing(_ctx, state) do
    {{:ok, demand: :input}, state}
  end

  @impl true
  def handle_write_list(:input, buffers, _ctx, state) do
    {{:ok, demand: {:input, length(buffers)}}, state}
  end
end
