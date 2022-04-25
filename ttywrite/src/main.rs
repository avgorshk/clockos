extern crate serial;
extern crate structopt;
extern crate xmodem;
#[macro_use] extern crate structopt_derive;

use std::path::PathBuf;
use std::time::Duration;

use structopt::StructOpt;
use serial::core::{CharSize, BaudRate, StopBits, FlowControl, SerialDevice, SerialPortSettings};
use xmodem::{Xmodem, Progress};

mod parsers;

use parsers::{parse_width, parse_stop_bits, parse_flow_control, parse_baud_rate};

#[derive(StructOpt, Debug)]
#[structopt(about = "Write to TTY using the XMODEM protocol by default.")]
struct Opt {
    #[structopt(short = "i", help = "Input file (defaults to stdin if not set)", parse(from_os_str))]
    input: Option<PathBuf>,

    #[structopt(short = "b", long = "baud", parse(try_from_str = "parse_baud_rate"),
                help = "Set baud rate", default_value = "115200")]
    baud_rate: BaudRate,

    #[structopt(short = "t", long = "timeout", parse(try_from_str),
                help = "Set timeout in seconds", default_value = "10")]
    timeout: u64,

    #[structopt(short = "w", long = "width", parse(try_from_str = "parse_width"),
                help = "Set data character width in bits", default_value = "8")]
    char_width: CharSize,

    #[structopt(help = "Path to TTY device", parse(from_os_str))]
    tty_path: PathBuf,

    #[structopt(short = "f", long = "flow-control", parse(try_from_str = "parse_flow_control"),
                help = "Enable flow control ('hardware' or 'software')", default_value = "none")]
    flow_control: FlowControl,

    #[structopt(short = "s", long = "stop-bits", parse(try_from_str = "parse_stop_bits"),
                help = "Set number of stop bits", default_value = "1")]
    stop_bits: StopBits,

    #[structopt(short = "r", long = "raw", help = "Disable XMODEM")]
    raw: bool,
}

pub fn noop(_: Progress) {  }

fn main() {
    use std::fs::File;
    use std::io::{BufReader, Read, Write};

    let opt = Opt::from_args();
    let mut serial = serial::open(&opt.tty_path).expect("path points to invalid TTY");

    let mut setting = serial.read_settings().expect("can not read TTY settings");
    setting.set_baud_rate(opt.baud_rate).expect("invalid baud rate");
    setting.set_char_size(opt.char_width);
    setting.set_flow_control(opt.flow_control);
    setting.set_stop_bits(opt.stop_bits);

    serial.write_settings(&setting).expect("invalid settings");
    let duration = Duration::new(opt.timeout, 0);
    serial.set_timeout(duration).expect("invalid timeout");

    let f = File::open(opt.input.expect("input file should be specified")).expect("input file is not found");
    let mut reader = BufReader::new(f);

    if opt.raw {
        let mut buffer = Vec::new();
        reader.read_to_end(&mut buffer).expect("unable to read file");
        serial.write_all(&buffer).expect("unable to write to TTY");
    } else {
        Xmodem::transmit_with_progress(reader, serial, noop).expect("Xmodem transmit failed");
    }
}
