defmodule Membrane.Demo.VideoDebug.Sink.Buffers do
  @moduledoc """
  Debug sink that inspect coming data. It makes demands in buffers.
  """

  use Membrane.Sink

  def_input_pad :input, demand_unit: :buffers, caps: :any

  @impl true
  def handle_prepared_to_playing(_ctx, state) do
    {{:ok, demand: :input}, state}
  end

  @impl true
  def handle_write(:input, buffer, _ctx, state) do
    IO.inspect(buffer)
    {:ok, state}
  end
end
