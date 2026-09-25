module tb_adders;

  reg a;
  reg b;
  reg cin;

  wire ha_sum;
  wire ha_carry;

  wire fa_sum;
  wire fa_carry;

  half_adder ha(
    .a(a),
    .b(b),
    .sum(ha_sum),
    .carry(ha_carry)
  );

  full_adder fa(
    .a(a),
    .b(b),
    .cin(cin),
    .sum(fa_sum),
    .carry(fa_carry)
  );

  initial begin
    $dumpfile("adders_wf.vcd");
    $dumpvars(0, tb_adders);

    $monitor("A=%b, B=%b, CIN=%b | HA_SUM=%b, HA_CARRY=%b, FA_SUM=%b, FA_CARRY=%b", a, b, cin, ha_sum, ha_carry, fa_sum, fa_carry);

    a=0; b=0; cin=0; #10;
    a=0; b=0; cin=1; #10;
    a=0; b=1; cin=0; #10;
    a=0; b=1; cin=1; #10;
    a=1; b=0; cin=0; #10;
    a=1; b=0; cin=1; #10;
    a=1; b=1; cin=0; #10;
    a=1; b=1; cin=1; #10;
  
    $finish;
  end

endmodule
