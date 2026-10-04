module tb_adders;
  parameter int WIDTH = 1;

  logic a1;
  logic b1;
  logic ha_sum;
  logic ha_cout;

  logic [WIDTH-1:0]a;
  logic [WIDTH-1:0]b;
  logic cin;
  logic [WIDTH-1:0] fa_sum;
  logic fa_cout;

  half_adder ha(
    .a(a1),
    .b(b1),
    .y(ha_sum),
    .c(ha_cout)
  );

  full_adder fa(
    .a(a),
    .b(b),
    .cin(cin),
    .y(fa_sum),
    .c(fa_cout)
  );

  initial begin
    $dumpfile("adders_waveform.vcd");
    $dumpvars(0, tb_adders);

    a1=1'b0; b1=1'b0; a=1'b0; b=1'b0; cin=1'b0; #10;
    a1=1'b0; b1=1'b0; a=1'b0; b=1'b0; cin=1'b1; #10;
    a1=1'b0; b1=1'b1; a=1'b0; b=1'b1; cin=1'b0; #10;
    a1=1'b0; b1=1'b1; a=1'b0; b=1'b1; cin=1'b1; #10;
    a1=1'b1; b1=1'b0; a=1'b1; b=1'b0; cin=1'b0; #10;
    a1=1'b1; b1=1'b0; a=1'b1; b=1'b0; cin=1'b1; #10;
    a1=1'b1; b1=1'b1; a=1'b1; b=1'b1; cin=1'b0; #10;
    a1=1'b1; b1=1'b1; a=1'b1; b=1'b1; cin=1'b1; #10;
  
    $finish;
  end

endmodule
