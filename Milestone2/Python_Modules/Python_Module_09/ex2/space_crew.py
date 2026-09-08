#!/usr/bin/env python3

from datetime import datetime
from typing import List
from enum import Enum
from pydantic import BaseModel, Field, ValidationError, model_validator


class Rank(str, Enum):
    CADET = "cadet"
    OFFICER = "officer"
    LIEUTENANT = "lieutenant"
    CAPTAIN = "captain"
    COMMANDER = "commander"


class CrewMember(BaseModel):
    member_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=2, max_length=50)
    rank: Rank
    age: int = Field(ge=18, le=80)
    specialization: str = Field(min_length=3, max_length=30)
    years_experience: int = Field(ge=0, le=50)
    is_active: bool = True


class SpaceMission(BaseModel):
    mission_id: str = Field(min_length=5, max_length=15)
    mission_name: str = Field(min_length=3, max_length=100)
    destination: str = Field(min_length=3, max_length=50)
    launch_date: datetime
    duration_days: int = Field(ge=1, le=3650)
    mission_status: str = "planned"
    budget_millions: float = Field(ge=1.0, le=10000.0)
    crew: List[CrewMember] = Field(min_length=1, max_length=12)

    @model_validator(mode="after")
    def validator(self) -> "SpaceMission":

        if not self.mission_id.startswith("M"):
            raise ValueError("Mission ID must start with M")

        if not any(
            c.rank in (Rank.CAPTAIN, Rank.COMMANDER) for c in self.crew
        ):
            raise ValueError(
                "Mission must have at least one Commander or Captain"
            )

        if not all(c.is_active for c in self.crew):
            raise ValueError("All crew members must be active")

        if self.duration_days > 365:
            experientes = sum(1 for c in self.crew if c.years_experience >= 5)
            if experientes * 2 < len(self.crew):
                raise ValueError(
                    "Long missions need at least 50% experienced crew"
                )

        return self
