import argparse
import re
from decimal import Decimal
from pathlib import Path

import cadquery as cq


HERE = Path(__file__).resolve().parent

INCH = Decimal("25.4")
NUMBER_9_CLEARANCE_DIAMETER = 5.0
CORNER_RADIUS_RATIO = 0.45
EDGE_SLOT_LENGTH = 10.0
EDGE_SLOT_SIZE = 2.0
EDGE_SLOT_HOOK_DEPTH = 2.0
EPSILON = 0.1


def parse_thickness(value):
    match = re.fullmatch(r"\s*(\d+(?:\.\d+)?|\.\d+)\s*(in|mm)\s*", value, re.I)
    if match is None:
        raise argparse.ArgumentTypeError("thickness must be a positive value like 1.5in or 38mm")

    amount = Decimal(match.group(1))
    if amount <= 0:
        raise argparse.ArgumentTypeError("thickness must be greater than zero")

    unit = match.group(2).lower()
    label = f"{format(amount.normalize(), 'f')}{unit}"
    thickness_mm = float(amount * INCH if unit == "in" else amount)
    return thickness_mm, label


def edge_slot(edge, center, thickness_mm):
    # In the side/top cross-section, cut a diagonal stripe where
    # EDGE_SLOT_HOOK_DEPTH <= inward + downward <= depth + size. This leaves
    # the outer corner intact as a triangular rope-retaining hook.
    depth = EDGE_SLOT_HOOK_DEPTH
    size = EDGE_SLOT_SIZE
    profile = (
        cq.Workplane("YZ")
        .polyline(
            (
                (depth + EPSILON, thickness_mm + EPSILON),
                (depth + size + EPSILON, thickness_mm + EPSILON),
                (-EPSILON, thickness_mm - depth - size - EPSILON),
                (-EPSILON, thickness_mm - depth - EPSILON),
            )
        )
        .close()
        .extrude(EDGE_SLOT_LENGTH)
    )
    if edge == "y_min":
        return profile.translate((center - EDGE_SLOT_LENGTH / 2, 0, 0))
    if edge == "x_min":
        return profile.translate((-EDGE_SLOT_LENGTH / 2, 0, 0)).rotate(
            (0, 0, 0), (0, 0, 1), -90
        ).translate((0, center, 0))
    raise ValueError(f"Unsupported slot edge: {edge}")


def make_spacer(name, length, width, hole_centers, thickness_mm, slot=None):
    corner_radius = min(length, width) * CORNER_RADIUS_RATIO
    spacer = (
        cq.Workplane("XY")
        .box(
            length,
            width,
            thickness_mm,
            centered=(False, False, False),
        )
        .edges("|Z")
        .fillet(corner_radius)
    )

    for x, y in hole_centers:
        hole = (
            cq.Workplane("XY")
            .center(x, y)
            .circle(NUMBER_9_CLEARANCE_DIAMETER / 2)
            .extrude(thickness_mm)
        )
        spacer = spacer.cut(hole)

    if slot is not None:
        spacer = spacer.cut(edge_slot(*slot, thickness_mm))

    step_path = HERE / f"{name}.step"
    stl_path = HERE / f"{name}.stl"
    cq.exporters.export(spacer, str(step_path))
    cq.exporters.export(
        spacer,
        str(stl_path),
        tolerance=0.03,
        angularTolerance=0.1,
    )
    return step_path, stl_path


def make_pulley_spacer(thickness_mm, label):
    # Match the complete pulley bottom's 39.5 x 32.6 mm YZ footprint, not just
    # the narrow paired mounting pads. The hole centers remain 25.5 mm apart.
    return make_spacer(
        f"end-pulley-ceiling-spacer-{label}",
        length=39.5,
        width=32.6,
        hole_centers=((7.0, 6.5), (32.5, 6.5)),
        thickness_mm=thickness_mm,
        slot=("y_min", 19.75),
    )


def make_elbow_spacer(thickness_mm, label):
    # Match the complete elbow's 51.4343 x 41.9 mm XY footprint. In this local
    # orientation X follows the elbow's original X axis and Y follows its
    # paired mounting-hole direction.
    return make_spacer(
        f"rope-elbow-ceiling-spacer-{label}",
        length=51.4343,
        width=41.9,
        hole_centers=((20.9905, 6.0), (20.9905, 35.9)),
        thickness_mm=thickness_mm,
        slot=("x_min", 20.95),
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate ceiling mount spacers.")
    parser.add_argument(
        "thickness",
        nargs="?",
        default="1.5in",
        type=parse_thickness,
        help="spacer thickness with unit, such as 1.5in or 38mm (default: 1.5in)",
    )
    args = parser.parse_args()
    thickness_mm, label = args.thickness
    for paths in (
        make_pulley_spacer(thickness_mm, label),
        make_elbow_spacer(thickness_mm, label),
    ):
        for path in paths:
            print(path)
