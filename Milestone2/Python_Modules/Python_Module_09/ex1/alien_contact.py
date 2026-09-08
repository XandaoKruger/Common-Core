#!/usr/bin/env python3

from datetime import datetime
from typing import Optional
from pydantic import BaseModel, Field, ValidationError, model_validator
from enum import Enum


class ContactType(str, Enum):
    RADIO = "radio"
    VISUAL = "visual"
    PHYSICAL = "physical"
    TELEPATHIC = "telepathic"


class AlienContact(BaseModel):
    contact_id: str = Field(min_length=5, max_length=15)
    timestamp: datetime
    location: str = Field(min_length=3, max_length=100)
    contact_type: ContactType
    signal_strength: float = Field(ge=0.0, le=10.0)
    duration_minutes: int = Field(ge=1, le=1440)
    witness_count: int = Field(ge=1, le=100)
    message_received: Optional[str] = Field(default=None, max_length=500)
    is_verified: bool = False

    @model_validator(mode="after")
    def validator(self) -> "AlienContact":

        if not self.contact_id.startswith("AC"):
            raise ValueError("Contact ID must start with AC")

        if self.contact_type == ContactType.PHYSICAL and not self.is_verified:
            raise ValueError("Physical contact reports must be verified")

        if (
            self.contact_type == ContactType.TELEPATHIC
            and self.witness_count < 3
        ):
            raise ValueError(
                "Telepathic contact requires at least 3 witnesses"
            )

        if self.signal_strength > 7.0 and self.message_received is None:
            raise ValueError(
                "Strong signals (> 7.0) should include received messages"
            )
        return self


def main() -> None:
    print("\n\033[32mAlien Contact Log Validator\033[m\n")

    print("=" * 60)

    print("Valid contact report:")

    contact = AlienContact(
        contact_id="AC_2024_001",
        timestamp=datetime.fromisoformat("2024-01-15T10:30:00"),
        location="Area 42, Lisboa",
        contact_type=ContactType.RADIO,
        signal_strength=8.5,
        duration_minutes=45,
        witness_count=5,
        message_received="Greetings from Zeta Reticuli",
        is_verified=True
    )

    print(f"ID: {contact.contact_id}")
    print(f"Type: {contact.contact_type.value}")
    print(f"Location: {contact.location}")
    print(f"Signal: {contact.signal_strength}/10")
    print(f"Duration: {contact.duration_minutes} minutes")
    print(f"Witnesses: {contact.witness_count}")
    print(f"Message: '{contact.message_received}'")

    print()
    print("=" * 60)

    print("\033[31mExpected validation error\033[m:")

    try:
        AlienContact(
            contact_id="AC_2024_001",
            timestamp=datetime.fromisoformat("2024-01-15T10:30:00"),
            location="Nuketown",
            contact_type=ContactType.TELEPATHIC,
            signal_strength=5.0,
            duration_minutes=99,
            witness_count=1,
            message_received="Kaboom"
        )
    except ValidationError as e:
        error_msg = e.errors()[0]["msg"].replace("Value error, ", "")
        print(error_msg)


if __name__ == "__main__":
    main()
