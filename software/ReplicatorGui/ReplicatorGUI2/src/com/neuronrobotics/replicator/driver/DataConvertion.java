package com.neuronrobotics.replicator.driver;

public class DataConvertion {
	/**
	 *** Encodes a <code>double</code> value into bytes
	 *** 
	 *** @param len
	 *            The number of bytes to encode the value to
	 *** @param val
	 *            The value to encode
	 *** 
	 * @return the bytes array created from the value
	 **/
	public static byte[] encodeDouble(int len, double val) {
		// 'len' must be at least 4
		if (len >= 4) {
			byte data[] = new byte[len];
			int flen = (len >= 8) ? 8 : 4;
			long n = (flen == 8) ? Double.doubleToRawLongBits(val)
					: (long) Float.floatToRawIntBits((float) val);
			// Big-Endian order
			for (int i = (flen - 1); i >= 0; i--) {
				data[i] = (byte) (n & 0xFF);
				n >>>= 8;
			}
			return data;
		} else {
			System.err.println("Wrong legnth byte array");
			return new byte[len];
		}
	}

	// ------------------------------------------------------------------------

	/**
	 *** Decodes a <code>double</code> value from bytes, using IEEE 754 format
	 *** 
	 * @param data
	 *            The byte array from which to decode the <code>double</code>
	 *            value
	 *** @param ofs
	 *            The offset into <code>data</code> to start decoding
	 *** @return The decoded value, or 0L
	 **/
	public static double decodeDouble(byte data[], int ofs) {
		// 'len' must be at lest 4
		if ((data != null) && (data.length >= 4)) {
			int len = data.length - ofs;
			int flen = (len >= 8) ? 8 : 4;
			long n = 0L;
			// Big-Endian order
			// { 0x01, 0x02, 0x03, 0x04 } -> 0x01020304
			for (int i = ofs; i < ofs + flen; i++) {
				n = (n << 8) | ((long) data[i] & 0xFF);
			}
			if (flen == 8) {
				return Double.longBitsToDouble(n);
			} else {
				return (double) Float.intBitsToFloat((int) n);
			}
		} else {
			return 0.0;
		}
	}
}
